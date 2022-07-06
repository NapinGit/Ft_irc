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
		std::string				_key;
		bool					_secure;
		
		std::vector<Client *> 	_operators;
	public:
		std::vector<Client *> 	_clients;
		
		Channel(std::string name, Client *cli);
		~Channel();
		bool present_or_not(Client *cli);
		bool present_or_not_operators(Client *cli);
		
		void leave_msg(Channel *chan, Client *cli, std::string arg);

		void add(Client *cli);
		void del(Client *cli);
		
		void add_operator(Client *cli);
		void del_operator(Client *cli);
	
		size_t nb_clients();
		
		std::string get_name() const;
		std::string get_hostname() const;
		std::string get_key() const;
		bool is_secure() const;

		void change_key(std::string key);
		void change_secure(bool mybool);



		/*std::vector<Client *> 	get_clients()
		{
			return _clients;
		}*/

		void change_hostname(const std::string &val);

		
		void send_to_chan(Client *from, std::string msg);
		void rpl_join(Client *from);
		void rpl_namreply(Client *from);
		void rpl_kick(Channel *chan, Client *cli, std::string arg);

};

template<class InputIterator, class T>
InputIterator find (InputIterator first, InputIterator last, const T& val);

#endif