#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "Client.hpp"
# include <vector>
class Client;

class Channel
{
	private:
		std::string 			_name;
		std::string 			_hostname;
		std::vector<Client *> 	_clients;
	public:
		Channel(std::string name, Client *cli);
		~Channel();
		bool present_or_not(Client *cli);
		
		void add(Client *cli);
		void del(Client *cli);
		
		void print_clients();
		
		std::string get_name() const;
		std::string get_hostname() const;

		void change_hostname(const std::string &val);

		
		void send_to_chan(Client *from, std::string msg);
		void rpl_join(Client *from);
		void rpl_namreply(Client *from);
};

#endif