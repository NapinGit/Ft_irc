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
class Server
{
	private:
		bool _alive;
		int _sock;
		const std::string _ip;
		const std::string _port;
		const std::string _password;

		void socket_init();
    public:
	Server(const std::string &port, const std::string &password);
	//Server(const Server&) = delete;
	//Server& operator=(const Server&) = delete;
	//Server(Server&&);
	//Server& operator=(Server&&);
	~Server();

	void start();
	
	//void stop();
	//void update();
	//std::unique_ptr<Messages::Base> poll();

	//private:
	//std::unique_ptr<ServerImpl> mImpl;
};
#endif