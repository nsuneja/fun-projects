#include "zmq.hpp"
#include "datatype.pb.h"
#include "SimpleRedisClient.h"
#include <memory>
#include <thread>
#include <map>

namespace plumgrid {

/**
* commands which can be executed on the chat prompt
*/
enum cmds {
    	HELP,
    	JOIN,
    	LEAVE,
    	LIST,
	EXIT,
	NO_CMD
};

class GroupChat {
public:
	GroupChat(std::string db_url);
	GroupChat();
	~GroupChat();
	
	/*
	* initializes the chat client
	*/
	void initialize();

	/**
	* starts the main prompt thread to execute commands on
	*/
	void run_prompt();
	
	/**
	* This method performs on the chat client resource cleanup on 'EXIT' command
	*/
	void cleanup();

private:
	static size_t MAX_CHANNEL_URL_LENGTH;
	static size_t MAX_CHAT_MSG_LENGTH;

	/**
	* stores the references of all the subscriber threads
	*/
	std::vector<std::shared_ptr<std::thread>> peer_data_channel_threads;

	/**
	* stores the references of the all the subscriber channels
	*/
	std::vector<std::shared_ptr<zmq::socket_t>> peer_data_channels;
	
	/*
	* global communication context
	*/
	zmq::context_t global_comm_ctx;

	/**
	* reference to the local publisher/data channel hosted by this client
	*/
	std::shared_ptr<zmq::socket_t> data_channel;

	/*
	* references to the local control channel hosted by the client
	*/
	std::shared_ptr<zmq::socket_t> control_channel;

	/*
	* local channels endpoint names
	*/
	channel_info local_channel;

	/**
	* reference to the local control channel thread
	*/
	std::shared_ptr<std::thread> local_control_channel_thread;


	/*
	* reference to the main prompt thread
	*/
	std::shared_ptr<std::thread> main_prompt_thread;

	/*
	* map to store the mapping between control and data channels of the peer clients
	*/
	std::map<std::string, std::string> data_to_control;

	/*
	* redis client object
	*/
	SimpleRedisClient logger;

	/*
	 *url of redis database
	*/
	std::string db_url;

	/*
	* this flag signals all the threads (subcribers threads and local control thread) to stop looping and exit
	*/
	volatile bool exit_flag;

	//this flag signals all the subscribers threads to stop looping and exit.
	//the local control thread still continues to run, when we leave the chat room
	volatile bool leave_room_flag; 

private:
	/**
	* run loop of the data channel thread. This thread accepts messages from the other peer clients.
	*/
	void data_channel_thread(std::shared_ptr<zmq::socket_t> subscriber);

	/**
	* subscribes the local client to a peer client's data channel
	*/
	void subscribe_to_data_channel(std::string data_channel_url);

	/**
	* run loop of the local control channel thread. This thread accepts control messages (get channel list, join/leave notifications) from peer clients
	*/
	void control_channel_thread(std::shared_ptr<zmq::socket_t> control_channel);

	/**
	* This method sends join notification from local client a peer's control channel.
	*/
	void send_join_notification(channel_info channel);

	/**
	* This method gets the list of all the members of a chat group from a peer client.
	*/
	channel_list get_channel_list (std::string peer_client);

	/**
	* This method gets the endpoint url of a socket.
	*/
	std::string get_endpoint_url(std::shared_ptr<zmq::socket_t> socket);

	/**
	* This method logs the chat messages to redis database.
	*/
	void log_message();

	/**
	* This method is called to leave the chat room. It::
	a) disconnects from all the subscribed channels
	b) send the LEAVE notification on al the subscribed channels
	c) signals all the data channel threads to terminate.
	*/
	void leave_room();

	/**
	This method is called the join a chat room. It::
	a) get the list of group members from the peer client.
	b) spawns one thread for each peer client and subscribes to the data channel of the peer client.
	c) sends join notification on the control channel of each of the peer clients.
	*/
	void join_room(std::string peer_client);
	
	/*
	* This method publishes the chat messages on local clients data channel, and logs the message to the central redis database.
	*/
	void publish_msg(std::string msg);

	/**
	* This method constitutes the loop of main prompt thread.
	*/
	void prompt_thread();

};

}
