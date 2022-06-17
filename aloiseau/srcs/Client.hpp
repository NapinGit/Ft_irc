#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
 #include "macro.hpp"
class Client
{
	private:
		bool				_auth;
		bool				_operator;
		std::string     	_nickname;
		std::string     	_user;
		const int	        _fd;

	public:
		Client(const int &fd);
		~Client();
		
		/*

			Accessor

		*/

		int get_fd() const;
		std::string get_user() const;
		std::string get_nickname() const;
		void send_to_client();
		bool get_auth() const;
		bool get_operator() const;

		/*

			Data modifier

		*/

		void change_auth(bool val);
		void change_nickname(std::string &val);
		void change_username(std::string &val);


		/*

			Utils

		*/
		void send_to_client(std::string &msg);

};
#endif