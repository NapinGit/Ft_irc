#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h> 
#include <stdlib.h> /* pour exit */
#include <string.h> /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h> /* pour htons et inet_aton */
#include <unistd.h> /* pour sleep */
#include <poll.h>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
 #include <signal.h> 
 #include <map>
 #include <netdb.h>
 #include "Client.hpp"
 #include "macro.hpp"

// void kill(*obj, int fd, char *arg);
typedef struct 	s_irc
{
	bool 								_alive;
	int 								_sock;
	 std::string 					_ip;
	 std::string 					_port;
	 std::string 					_password;
	std::vector<pollfd>					mypoll;
	std::map<int , Client *> 			clients;
	std::map <std::string, void (*)(struct s_irc *obj, int fd, char *arg)> 	cmd;

}				t_irc;

 #include "Command/command.hpp"

class Server
{
	public:
		// typedef std::vector<pollfd> obj->mypoll;

	private:
		t_irc obj;


		// bool _alive;
		// int _sock;

		// const std::string _ip;
		// const std::string _port;
		// const std::string _password;
		// std::vector<pollfd>	mypoll;
		// std::map<int , Client *> clients;
		// std::map <std::string, void (*)()> cmd;

		void socket_init();
    public:


	Server(const std::string &port, const std::string &password);
	//Server(const Server&) = delete;
	//Server& operator=(const Server&) = delete;
	//Server(Server&&);
	//Server& operator=(Server&);
	~Server();

	void start();
	void connecting_client();
	void read_msg(pollfd &client);
	void close_con(std::vector<pollfd>::iterator it);
	void signal_handler(int signal);
	void get_client_info(pollfd &client);
	void reset_revent();
	void init_cmd();

	//void stop();
	//void update();
	//std::unique_ptr<Messages::Base> poll();

	// void kiall();
	// void kialla();
	//private:
	//std::unique_ptr<ServerImpl> mImpl;
};
#endif