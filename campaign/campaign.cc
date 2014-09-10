#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <set>
#include <string>
#include <iostream>

//since the problem statement states that the machine has 8 cores
//also considering a hyperthreading factor of 2
#define NUM_THREADS 16 

using namespace std;

//campaign information
typedef struct campaign_info {
     set<unsigned int> segments;
     string name;
} campaign_info;

//individual user record
typedef struct user_record {
     vector<unsigned int> segments;
} user_record;

//contains all the campaign information
vector<campaign_info> campaigns;

//stores the user data from the standard input
vector<user_record*> user_input;

//number of input records processed by the io thread
volatile unsigned int cur_input_offset;

//end of input flag
volatile bool end_of_input=false;

void * worker_routine(void* arg);
void * io_routine (void* arg); 

pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Each thread process one user record in each iteration
 */
void * worker_routine(void* arg)
{
	unsigned int index = *(static_cast<unsigned int*>(arg));

	//next input to be processed
	unsigned long next_input_index = index;
	unsigned long cur_input_offset_t=0;
	bool end_of_input_t=false;

	//loop, and process one user input on each iteration
	while (true) {
		
		//accquire the rw lock
		pthread_rwlock_rdlock(&lock_rw);
		cur_input_offset_t=cur_input_offset;
		end_of_input_t=end_of_input;
		pthread_rwlock_unlock(&lock_rw);

		//break if no more input to process
		if (next_input_index >= cur_input_offset_t  && end_of_input_t) {
			break;
		}
	
		//check if the record is available
		if (cur_input_offset_t > next_input_index) {
			
			//process the record, accquire the rwlock before that
			pthread_rwlock_rdlock(&lock_rw);
		        user_record* user_rec = user_input[next_input_index];
			pthread_rwlock_unlock(&lock_rw);

			//this map stores the number of user record segments existing in a campaign
		        vector<unsigned int> segment_count(campaigns.size(),0);	
 
			size_t max_count=0;
			//iterate through the record
			for (unsigned int i=0; i < user_rec->segments.size(); i++ ) {

				//iterate through the campaigns
				for ( unsigned int j=0; j < campaigns.size(); j++) {
					campaign_info& campaign = campaigns[j];
					//if (campaign.name == "reticulates")
					//	asm("int $3");					
	
					//check if the campaign contains a segment
					if (campaign.segments.find(user_rec->segments[i]) != campaign.segments.end()) {
						segment_count[j]++;
					        if (segment_count[j] > max_count) {
							max_count = segment_count[j];
						}	
					}
				}	
			}

			//roll a dice and select a max_index
			unsigned int lucky_index=0;
			//hold a vector of campaigns with max counts
			vector<unsigned int> max_count_indices;
			if (max_count) {
				for (unsigned int i=0; i < segment_count.size(); i++) {
					if (segment_count[i] == max_count) {
						max_count_indices.push_back(i);
					}
				}

				//if (max_count == 2)
				//	asm("int $3");
				//lucky campaign
				lucky_index = rand()%(max_count_indices.size());
			}

				
			//lock the output mutex
			pthread_mutex_lock(&output_mutex);
			//print the record
			for (unsigned int i=0; i < user_rec->segments.size(); i++)
				cout << user_rec->segments[i] << " ";
			cout << "\n";
			if (!max_count)
			{
				//asm("int $3");
				cout << "no campaign\n";
			}
			else
				cout << campaigns[max_count_indices[lucky_index]].name << "\n";			
			pthread_mutex_unlock(&output_mutex);

			//erase the user input from the vector
			delete user_rec;
			
			//increment the next_page_index for this thread
			next_input_index+=NUM_THREADS-1;
		}
	}

	return 0;
}

/**
 * io thread to process the input from the standard in and populate the user_input vector
 */
void * io_routine (void* arg) 
{
	char* line=0;
	size_t count=0, len=0;
	int read=0;
        while ((read = getline(&line, &len, stdin)) != -1) {

		//read the next user data row
		char* segment_str=strtok(line," ");
		vector<unsigned int> input_row;
		while (segment_str) {
			//get the segment number
			unsigned int segment = atoi(segment_str);
		
			//insert the segment into vector
			input_row.push_back(segment);
			
			//read the next segment
			segment_str=strtok(NULL," ");	
		}
	
		//increment the record count	
		count++;

		//create a user record object, and insert into the user_input buffer
		user_record* rec = new user_record;
		rec->segments=input_row;

		//accquire the writer lock and increment the offset
		pthread_rwlock_wrlock(&lock_rw);
		//insert the row
		user_input.push_back(rec);
		cur_input_offset=count;
		pthread_rwlock_unlock(&lock_rw);
        }

	//set the end of input flag		
	pthread_rwlock_wrlock(&lock_rw);
	end_of_input=true;
	pthread_rwlock_unlock(&lock_rw);

	return 0;
}

/*
 * This method pre processes the campaign data
 */
void preprocess_campaign_data(FILE* fp) 
{
        //read each campign info
        char* line=NULL;
	int read=0;
	size_t len=0;
        while ((read = getline(&line, &len, fp)) != -1) {
		
		//read the name
		char* token = strtok(line," ");
		campaign_info campaign;
		campaign.name=string(token);

		//read the segments
		char* segment_str=strtok(NULL," ");
		while(segment_str) {
			//get the segment number
			unsigned int segment = atoi(segment_str);

			//insert the segment into the segment set
			campaign.segments.insert(segment);
		
			//read the next segment
			segment_str=strtok(NULL," ");	
		}

		//insert the campaign struct
		campaigns.push_back(campaign);
        }
} 

int main(int argc, char* argv[]) 
{
	if (argc < 2) {
		printf("usage:: ./campaign <file_name>");
		exit(0);
	}

	FILE* fp = fopen(argv[1],"r");
	if (!fp) {
		printf("An error occured while opening the file. error number: %d\n", errno);
		exit(1);
	}

	//pre process the campaign data
	preprocess_campaign_data(fp);

	//create a set of worker threads
	pthread_t worker_threads[NUM_THREADS-1];
	pthread_t io_thread;

	//start the io thread
	pthread_create(&io_thread, 0, io_routine, 0);

	//start the worker threads
	int i=0;
	for (i=0; i < NUM_THREADS-1; i++)
	{
		unsigned int* index_ptr = new unsigned int;
		*index_ptr=i;	
		pthread_create(&worker_threads[i], 0 , worker_routine, (void*)index_ptr);
	}
	
	void* ret_val;
	//wait for io and worker threads to join
	pthread_join(io_thread, &ret_val);
	for (i=0; i < NUM_THREADS-1; i++)
		pthread_join(worker_threads[i], &ret_val);

	return 0;
}
