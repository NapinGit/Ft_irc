#ifndef CLIENT_HPP
# define CLIENT_HPP
# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <map>
# include "Channel.hpp"
class Channel;

class Client
{
	private:
		bool				_auth;
		bool				_operator;
		std::string     	_nickname;
		std::string     	_hostname;
		std::string     	_user;
		const int	        _fd;

	public:
		std::map<std::string , Channel *> 	_channels;
		Client(const int &fd);
		~Client();
		
		/*

			Accessor

		*/

		int get_fd() const;
		std::string get_user() const;
		std::string get_nickname() const;
		std::string get_hostname() const;
		void send_to_client(Client *from, const std::string msg);
		void send_to_client(Client *from, const char *msg);
		bool get_auth() const;
		bool get_operator() const;

		/*

			Data modifier

		*/

		void add_channel(Channel *chan);
		void change_auth(bool val);
		void change_nickname(std::string &val);
		void change_username(std::string &val);
		void change_hostname(std::string &val);

};
#endif