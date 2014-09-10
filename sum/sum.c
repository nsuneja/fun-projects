#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096
//since the problem statement states that the machine has 8 cores
//also considering a hyperthreading factor of 2
#define NUM_THREADS 16

void * worker_routine(void* arg);
void * io_routine (void* arg); 

pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;
volatile unsigned long cur_page_count;
unsigned char* buf;
unsigned long result[NUM_THREADS-1];
unsigned long file_size;
unsigned long total_alloc_size;

/**
 * Each thread reads one page i.e. 1024 integers in one iteration, and sum them
 */
void * worker_routine(void* arg)
{
	//casting from pointer to integer to get the result index
	int index = ((int)arg);
	unsigned long sub_sum = 0;

	//next page to be read
	unsigned long next_page_index = index;
	unsigned long tmp_page_count=0;

	//loop, and add one page of integers in each iteration
	while (1) {

		if (next_page_index >= total_alloc_size/PAGE_SIZE)
			break;
	
		//accquire the rw lock
		pthread_rwlock_rdlock(&lock_rw);
		tmp_page_count=cur_page_count;
		pthread_rwlock_unlock(&lock_rw);

		//check if the page is available
		if (tmp_page_count > next_page_index) {

			//read the integers from this page
			for (int i=0; i < PAGE_SIZE/4; i++ ) {
				unsigned char* ptr = buf + next_page_index*PAGE_SIZE + 4*i;
				
				//dont read across the file boundary
				if (ptr >= buf + file_size) 
					break;
			
				//since the provided architecture and the input data file is little endian
				unsigned int tmp = ((unsigned int)(ptr[3] << 24)) + ((unsigned int)(ptr[2] << 16)) + ((unsigned int)(ptr[1] << 8)) + ((unsigned int)ptr[0]);
				sub_sum += tmp;
			}

			//the page has been summed, so we can free the memory
			munmap(buf + next_page_index*PAGE_SIZE, PAGE_SIZE);

			//increment the next_page_index for this thread
			next_page_index+=NUM_THREADS-1;
		}
	}

	//insert the result
	result[index]=sub_sum;

	return 0;
}

void * io_routine (void* arg) 
{
	FILE* fp = (FILE*)arg;

	//allocate the memory for the same
	//buf = mmap(0, total_alloc_size,  PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0);
	//buf=malloc(total_alloc_size);
	buf = (unsigned char*)sbrk(total_alloc_size);

	//read the file contents into memory, page by page
	while ( fread(buf + PAGE_SIZE*cur_page_count, 4, PAGE_SIZE/4, fp) == PAGE_SIZE/4) {
		pthread_rwlock_wrlock(&lock_rw);
		cur_page_count++;
		pthread_rwlock_unlock(&lock_rw);
	}

	//we have read the last page
	pthread_rwlock_wrlock(&lock_rw);
	cur_page_count++;
	pthread_rwlock_unlock(&lock_rw);

	return 0;
} 

int main(int argc, char* argv[]) 
{
	if (argc < 2) {
		printf("usage:: ./sum <file_name>");
		exit(0);
	}

	FILE* fp = fopen(argv[1],"r");
	if (!fp) {
		printf("An error occured while opening the file. error number: %d\n", errno);
		exit(1);
	}

	//determine file size
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	//round up the allocation size to the nearest page size
	total_alloc_size = file_size + ( PAGE_SIZE - file_size%PAGE_SIZE);

	//create a set of worker threads
	pthread_t worker_threads[NUM_THREADS-1];
	pthread_t io_thread;
	
	//start the io thread
	pthread_create(&io_thread, 0, io_routine, (void*)fp);

	//start the worker threads
	int i=0;
	for (i=0; i < NUM_THREADS-1; i++)
		pthread_create(&worker_threads[i], 0 , worker_routine, (void*)i);

	void* ret_val;
	//wait for io and worker threads to join
	pthread_join(io_thread, &ret_val);
	fclose(fp);
	for (i=0; i < NUM_THREADS-1; i++)
		pthread_join(worker_threads[i], &ret_val);

	//sum up the result
	unsigned long sum=0;
	for (i=0;i < NUM_THREADS-1;i++) {
		sum+=result[i];	
	}

	printf("%ld\n", sum);

	return 0;
}
