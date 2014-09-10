#include "client.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <time.h>
using namespace std;

namespace plumgrid {

size_t GroupChat::MAX_CHANNEL_URL_LENGTH=1024;
size_t GroupChat::MAX_CHAT_MSG_LENGTH=1024;

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(std::string const &input) { 
    std::istringstream buffer(input);
    std::vector<std::string> ret;

    std::copy(std::istream_iterator<std::string>(buffer), 
              std::istream_iterator<std::string>(),
              std::back_inserter(ret));
    return ret;
}
       
GroupChat::GroupChat() : global_comm_ctx(1), exit_flag(false), leave_room_flag(false)  {}

GroupChat::GroupChat(string db_url) : global_comm_ctx(1), db_url(db_url), exit_flag(false), leave_room_flag(false) {}


GroupChat::~GroupChat() 
{
}

std::string GroupChat::get_endpoint_url(std::shared_ptr<zmq::socket_t> socket)
{
	size_t size;
	char data[MAX_CHANNEL_URL_LENGTH];
	socket->getsockopt( ZMQ_LAST_ENDPOINT, &data, &size);
	return string(data);
}

void GroupChat::data_channel_thread(std::shared_ptr<zmq::socket_t> subscriber)
{
	while (true) {
		zmq::message_t msg;
		if (exit_flag || leave_room_flag) //signal to end the thread
			break;
	    	if (subscriber->recv(&msg) == 0) //receive in a non blocking manner
			continue;
		chat c;
	    	c.ParseFromString(string(static_cast<char*>(msg.data())));
		if (c.contents() == "<EOF>") { //clearing up the resources, not the best solution, but will work
			string data_channel_url = get_endpoint_url(subscriber);
			//disconnect from the publisher
			subscriber->disconnect(data_channel_url.data());
			subscriber->close();
			//remove the mapping
			string control_channel_url = data_to_control[data_channel_url];
			data_to_control.erase(data_channel_url);
			//print notification
			cout << "client:: " << control_channel_url.substr(6) << " just left the group!!!\n" << std::flush;

			//exit this thread
			break;
		}
		cout << "message received from:: "  << data_to_control[get_endpoint_url(subscriber)]  <<  ":: "<< c.contents() << std::endl << std::flush;
	}
}

void GroupChat::subscribe_to_data_channel(string data_channel_url) {

	//subscribe to data/publisher channel
	std::shared_ptr<zmq::socket_t> subscriber = std::make_shared<zmq::socket_t>(global_comm_ctx, ZMQ_SUB);
	peer_data_channels.push_back(subscriber);
	subscriber->connect(data_channel_url.data());
	subscriber->setsockopt(ZMQ_SUBSCRIBE, "", 0);
	//set the recv timeout=100ms
	int timeout=100;
	subscriber->setsockopt(ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
	auto subscriber_thread = std::make_shared<thread>(&GroupChat::data_channel_thread, this, subscriber);
	//store the reference to the thread
	peer_data_channel_threads.push_back(subscriber_thread);
}


void GroupChat::control_channel_thread(std::shared_ptr<zmq::socket_t> control_channel) 
{
	//cout << "inside control thread\n";
	zmq::message_t msg;
	while (true) {
		
		if (exit_flag) //signal to exit the thread
			break;
	
		if (control_channel->recv(&msg) == 0) //non blocking way
			continue; 
		
		control_msg msg_obj;
	    	msg_obj.ParseFromString(string(static_cast<char*>(msg.data())));
	
		switch(msg_obj.type()) {
			case control_msg_Type_GET_CHANNELS:
			{
				channel_list channels;
				for (auto it : data_to_control) {
					//add the channels to the list
					channel_info* channel = channels.add_channel();
					channel->set_data_url(it.first);
					channel->set_control_url(it.second);
				}

	    			string buffer;
	    			channels.SerializeToString(&buffer);
	    			//send the channel list
	    			control_channel->send(static_cast<const void*>(buffer.data()), buffer.length());
				break;
			}
			case control_msg_Type_JOIN_NOTIFICATION:
			{
				//enter the room
				leave_room_flag=false;

				channel_info channel = msg_obj.channel();
				//subscribe to the new data channel
				subscribe_to_data_channel(channel.data_url());
				//add a mapping
				data_to_control[channel.data_url()]=channel.control_url();
				//send ack
				ack a;
	    			string buffer;
	    			a.SerializeToString(&buffer);
	    			control_channel->send(static_cast<const void*>(buffer.data()), buffer.length());

				//display the notification on the user screen
				cout << "client:: " << channel.control_url().substr(6) << " just joined the group!!!\n" << std::flush;
				
				break;
			}
			case control_msg_Type_LEAVE_NOTIFICATION:
				//Unimplemented...Handled on the data channel
				break;
			default:
				cerr << "Unexpected control msg. Ignoring..\n"; 
		}
	}
}


void GroupChat::send_join_notification(channel_info channel) {

		//send join notification to each control channel
		zmq::socket_t join_notif_soc(global_comm_ctx, ZMQ_REQ);
		join_notif_soc.connect(channel.control_url().data());

		//create notification
	    	std::shared_ptr<control_msg> join_notif = std::make_shared<control_msg>();
		join_notif->set_type(control_msg_Type_JOIN_NOTIFICATION);
		join_notif->mutable_channel()->CopyFrom(local_channel);
		string buffer;
		join_notif->SerializeToString(&buffer);

		//send the request
		join_notif_soc.send(static_cast<const void*>(buffer.data()), buffer.length());

		//wait for the ack
		zmq::message_t msg;
		join_notif_soc.recv(&msg);
}

channel_list  GroupChat::get_channel_list (string peer_client) 
{
	    //get the data channel list
	    zmq::socket_t channel_list_soc(global_comm_ctx, ZMQ_REQ);
	    channel_list_soc.connect(peer_client.data());

	    //create the control msg
	    std::shared_ptr<control_msg> get_channel_list = std::make_shared<control_msg>();
	    get_channel_list->set_type(control_msg_Type_GET_CHANNELS);	
	    string buffer;
	    get_channel_list->SerializeToString(&buffer);

	    //send the request
	    channel_list_soc.send(static_cast<const void*>(buffer.data()), buffer.length());

	    //wait for the data channel list
	    zmq::message_t msg;
	    channel_list_soc.recv(&msg);
	    channel_list ch_list;
	    ch_list.ParseFromString(string(static_cast<char*>(msg.data())));
	
	    return ch_list; 			
}


void GroupChat::initialize()
{
	//publisher channel
 	data_channel = std::make_shared<zmq::socket_t>(global_comm_ctx, ZMQ_PUB);
	data_channel->bind("tcp://127.0.0.1:0");

	//control channel
	control_channel = std::make_shared<zmq::socket_t>(global_comm_ctx, ZMQ_REP);
	control_channel->bind("tcp://127.0.0.1:0");
	//set the recv timeout=100ms
	int timeout=100;
	control_channel->setsockopt(ZMQ_RCVTIMEO, &timeout, sizeof(timeout));

	//set the local publisher and local control channels
	local_channel.set_data_url(get_endpoint_url(data_channel));
	local_channel.set_control_url(get_endpoint_url(control_channel));

	cout << "client endpoint::" << local_channel.control_url().substr(6) << std::endl;
	//cout << "data channel::" << data_channel_url << std::endl;
		
	//add the local control and local publisher urls
	data_to_control[local_channel.data_url()]=local_channel.control_url();
	
	//start the contol channel thread
	local_control_channel_thread = std::make_shared<std::thread>(&GroupChat::control_channel_thread, this, control_channel);

	//connect to redis database for logging
	if(!db_url.empty()) {
		vector<string> tokens = split(db_url, ':');
		logger.redis_conect(tokens[0].data(), stoi(tokens[1]));
		logger.LogLevel(0);
	}
}

cmds get_cmd(std::string str_cmd)
{
	if (str_cmd == "<help>" || str_cmd == "<HELP>") return cmds::HELP;
	if (str_cmd == "<join>" || str_cmd == "<JOIN>") return cmds::JOIN;
	if (str_cmd == "<leave>" || str_cmd == "<LEAVE>") return cmds::LEAVE;
	if (str_cmd == "<exit>" || str_cmd == "<EXIT>") return cmds::EXIT;
	if (str_cmd == "<list>" || str_cmd == "<LIST>") return cmds::LIST;
	return cmds::NO_CMD;
}

void GroupChat::join_room(string peer_client) 
{
	//unset the leave room flag
	leave_room_flag=false;

	//get the data channel list
	channel_list channels= get_channel_list(peer_client);

	//ensure that i am not already in the chat room
	for (int i=0; i < channels.channel_size(); i++) {
		const channel_info& channel = channels.channel(i);
		if (channel.control_url() == local_channel.control_url()) {
			cout << "local client is already in the chat room\n";
			return;
		}
	}

	//subscribe to data channels
	for (int i=0;i<channels.channel_size();i++) {
		channel_info channel = channels.channel(i);
		//create a mapping from data to control channel
		data_to_control[channel.data_url()] = channel.control_url();
		//subscribe to the data channels
		subscribe_to_data_channel(channel.data_url());
	}

	for (int i=0;i<channels.channel_size();i++) {
		channel_info channel = channels.channel(i);
		//send the join notification to each member in the group
		send_join_notification(channel);
	}
}

void GroupChat::leave_room()
{
	//set the leave room flag, signal the subscriber threads
	leave_room_flag=true;

	//send the EOF message on the data channel
	chat c;
	c.set_contents("<EOF>");	
	string buffer;
	c.SerializeToString(&buffer);

	//send the leave request
	data_channel->send(static_cast<const void*>(buffer.data()), buffer.length());

	//wait for all the subscriber threads to exit
	for (auto thread: peer_data_channel_threads) {
		if (thread->joinable())
			thread->join();
	}

	//do local cleanup
	for (auto subscriber: peer_data_channels) {
		if (subscriber->connected()) {
			string data_channel_url = get_endpoint_url(subscriber);
			//remove entry from the map
			data_to_control.erase(data_channel_url);
		
			//close connection
			subscriber->disconnect(data_channel_url.data());
			subscriber->close();
		}
	}

	//cleanup the peer data channels
	peer_data_channels.clear();
	//cleanup the thread object references
	peer_data_channel_threads.clear();	
}

void GroupChat::publish_msg(string msg)
{
	//create the data msg
	chat c;
	c.set_contents(msg);	
	string buffer;
	c.SerializeToString(&buffer);

	//send the request
	data_channel->send(static_cast<const void*>(buffer.data()), buffer.length());

	//log to the database
	if (logger) { // Operator  bool  () tells us if the connection exists or not

		std::time_t cur_time = std::time(NULL);
		string time_str = std::to_string(cur_time);

		//database key is the concatenation of epoch time and client id.
		string db_key = time_str + "," + local_channel.control_url();

		//serialize the msg to replace all whitespace characters with an '_', redis requirement
		string new_msg;
		for (auto ch: msg) {
			if (isspace(ch)) {
				new_msg.push_back('_');
			} else
				new_msg.push_back(ch);
		}

		//insert into db
		logger.set(db_key.data(), new_msg.data());
	}
}

void GroupChat::prompt_thread()
{
	cout << "WELCOME TO GROUP CHAT\n";

	//propmt for messages
	string msg;
	while (true) {
		cout << "$$ " << std::flush;
		getline (cin, msg);

		vector<string> tokens = split(msg);
		if (tokens.size() > 0 ) {

			switch (get_cmd(tokens[0])) {
				case cmds::HELP:
				{
					cout << "The list of available commands are:\n";
					cout << "1) <HELP>, provides the help menu\n";
					cout << "2) <JOIN> <peer-client>, joins the chat room in which the peer client is \n";
					cout << "3) <LIST>, shows all the members in your chat toom\n";
					cout << "4) <LEAVE>, leave the chat room\n";
					cout << "5) <EXIT>, exit the chat client\n";
					cout << "NOTE::Any other message is interpreted as a chat message\n";
					break;
				}
				case cmds::JOIN: 
				{
					if (tokens.size() < 2) {
						cout << "incorrect usage. correct usage:: <join> \"peer client\" \n" << std::flush;
						continue;
					}
					string peer_client = tokens[1];
			
					//check that i am not subscribing to my local channel
					if (peer_client == local_channel.control_url().substr(6)) {
						cout << "cannot subscribe to your local channel\n";
						continue;
					}					

					join_room("tcp://" + peer_client); 
					break;
				}
				case cmds::LIST:
					cout << "Group Members::\n";
					for (auto it: data_to_control) {
						string channel = it.second;
						cout << channel.substr(6) << std::endl;
					}
					break;
				case cmds::LEAVE:
				{
					leave_room();
					break;
				}
				case cmds::EXIT:
				{
					leave_room();
					exit_flag=1;
					//exit the prompt thread
					return;
				}
				default: 
					publish_msg(msg);
			}
		}
	}

}

void GroupChat::run_prompt() 
{
	main_prompt_thread = std::make_shared<std::thread>(&GroupChat::prompt_thread, this);
	main_prompt_thread->join(); 
}


void GroupChat::cleanup() 
{
	//wait for control thread to return
	if (local_control_channel_thread->joinable())
		local_control_channel_thread->join();	
	
	//do the exit cleanup
	//tear down the local control and data channels
	control_channel->close();
	data_channel->close();

	//close the connection to the database
	if (logger) // operator bool () overload tells us if the connection exists
		logger.redis_close();

}

}

int main (int argc, char *argv[])
{
	//create a GroupChat instance
	std::unique_ptr<plumgrid::GroupChat> gc;
	if (argc < 2)
		gc = std::unique_ptr<plumgrid::GroupChat>(new plumgrid::GroupChat());
	else
		gc = std::unique_ptr<plumgrid::GroupChat>(new plumgrid::GroupChat(argv[1]));

	gc->initialize();
	gc->run_prompt();
	gc->cleanup();	

	return 0;
}
