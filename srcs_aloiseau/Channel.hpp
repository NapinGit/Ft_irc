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
		std::vector<Client *> 	_operators;
	public:
		Channel(std::string name, Client *cli);
		~Channel();
		bool present_or_not(Client *cli);
		bool present_or_not_operators(Client *cli);
		
		void add(Client *cli);
		void del(Client *cli);
		
		void add_operator(Client *cli);
		void del_operator(Client *cli);
		void print_clients();
		
		std::string get_name() const;
		std::string get_hostname() const;

		void change_hostname(const std::string &val);

		
		void send_to_chan(Client *from, std::string msg);
		void rpl_join(Client *from);
		void rpl_namreply(Client *from);
		//std::vector<Client *> 	_clients;
		std::vector<Client *> get_client();
		std::vector<Client *> get_operator();
};

#endif