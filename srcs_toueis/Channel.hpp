#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "Client.hpp"
# include <vector>
class Client;

class Channel
{
	private:
		std::string 			_name;
		std::vector<Client *> 	_clients;
	public:
		Channel(std::string name, Client *cli);
		~Channel();
		bool present_or_not(Client *cli);
		void add(Client *cli);
		void del(Client *cli);
		void print_clients();
		std::string get_name();
		void send_to_chan(Client *from, std::string msg);

};

#endif