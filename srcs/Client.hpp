#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h> 
class Client
{
	private:
		 std::string     	_nickname;
		 std::string     	_user;
		 int        		_fd;

	public:
		Client(const std::string &nickname, const std::string &user, const int &fd);
		~Client();
		int get_fd() const;
		std::string get_user() const;
		std::string get_nickname() const;
};
#endif