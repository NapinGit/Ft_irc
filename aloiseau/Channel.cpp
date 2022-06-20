#include "Channel.hpp"

template<class InputIterator, class T>
InputIterator find (InputIterator first, InputIterator last, const T& val)
{
	while (first!=last) {
	if (*first==val) return first;
	++first;
	}
	return last;
}

Channel::Channel(std::string name, Client *cli): _name(name)
{
	_clients.push_back(cli);
}

Channel::~Channel()
{}

bool Channel::present_or_not(Client *cli)
{
	if (find(_clients.begin(), _clients.end(), cli) == _clients.end())
		return false;
	return true;
}

bool Channel::present_or_not_operators(Client *cli)
{
	if (find(_operators.begin(), _operators.end(), cli) == _operators.end())
		return false;
	return true;
}

void Channel::add(Client *cli)
{
	if (!present_or_not(cli))
		_clients.push_back(cli);
}

void Channel::del(Client *cli)
{
	std::vector<Client *>::iterator it = find(_clients.begin(), _clients.end(), cli);

	if (it != _clients.end())
	{
		//leave channel message to all other clients on channel
		_clients.erase(find(_clients.begin(), _clients.end(), cli));
	}

}

void Channel::add_operator(Client *cli)
{
	if (!present_or_not_operators(cli))
		_operators.push_back(cli);
}

void Channel::del_operator(Client *cli)
{
	std::vector<Client *>::iterator it = find(_operators.begin(), _operators.end(), cli);

	if (it != _operators.end())
	{
		_operators.erase(find(_operators.begin(), _operators.end(), cli));
	}

}


void Channel::print_clients()
{
	std::vector<Client *>::iterator it;
	std::vector<Client *>::iterator ite;

	std::cout << "list of clients"<< std::endl;
	for(it = _clients.begin(), ite = _clients.end(); it != ite ; it++)
	{
		std::cout << "\t" << (*it)->get_nickname() << std::endl;
	}
}

std::string Channel::get_name() const
{
	return (_name);
}

void Channel::send_to_chan(Client *from, std::string msg)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();

	while (it != ite)
	{
		if (from != (*it))
		{
	        // std::cout << "ARG" << from->get_nickname() <<  std::endl;
			std::string str = ":" + from->get_nickname() + " PRIVMSG #" + _name + " :" + msg + "\r\n";
			send((*it)->get_fd(), str.c_str(), str.length(), 0);

			// send((*it)->get_fd(), ":", 1, 0);
			// send((*it)->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
			// send((*it)->get_fd(), " PRIVMSG #", 10, 0);
			// send((*it)->get_fd(), _name.c_str(), _name.size(), 0);
			// send((*it)->get_fd(), " :", 2, 0);
			// send((*it)->get_fd(), msg.c_str(), msg.size(), 0);
			// send((*it)->get_fd(), "\r\n", 2, 0);
		}
		it++;
	}
}

void Channel::rpl_join(Client *from)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();
	std::string str;

	while (it != ite)
	{
		str = ":" + from->get_nickname() + "!" + from->get_username() + "@" + from->get_hostname() + " JOIN #" + _name + "\r\n" ;
		send((*it)->get_fd(), str.c_str(), str.length(), 0);
		str.clear();
			// send((*it)->get_fd(), ":", 1, 0);
			// send((*it)->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
			// send((*it)->get_fd(), "!", 1, 0);
			// send((*it)->get_fd(), from->get_username().c_str(), from->get_nickname().size(), 0);
			// send((*it)->get_fd(), "@", 1, 0);
			// send((*it)->get_fd(),  from->get_hostname().c_str(), from->get_hostname().size(), 0);
			// send((*it)->get_fd(), " JOIN #", 7, 0);
			// send((*it)->get_fd(), _name.c_str(), _name.size(), 0);
			// send((*it)->get_fd(), "\r\n", 2, 0);
		// }
		it++;
	}
}

void Channel::rpl_namreply(Client *from)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();

//topic reply

	// send(from->get_fd(), ":", 1, 0);
	// send(from->get_fd(), _hostname.c_str(), _hostname.size(), 0);
	// send(from->get_fd(), " 332 ", 5, 0);
	// send(from->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
	// send(from->get_fd(), " #", 2, 0);
	// send(from->get_fd(), _name.c_str(), _name.size(), 0);
	// send(from->get_fd(), " :", 2, 0);
	// send(from->get_fd(), "TOPIC", 5, 0);
	// send(from->get_fd(), "\r\n", 2, 0);


//list of user on channel rpl and endoflist
	//begin list
	std::string list = ":" + _hostname + " 353 " + from->get_nickname() + " = #" + _name + " :";
	while (it != ite)
	{
		if (present_or_not_operators(*it))
			list = list + " @" + (*it)->get_nickname();
		else
			list = list + " " + (*it)->get_nickname();
		it++;
	}
	list = list + "\r\n";
	send(from->get_fd(), list.c_str(), list.length(), 0);

	//end list
	list.clear();
	list = ":" + _hostname + " 366 " + from->get_nickname() + " #" + _name +  " :End of NAMES list\r\n";
	send(from->get_fd(), list.c_str(), list.length(), 0);

	// send(from->get_fd(), ":", 1, 0);
	// send(from->get_fd(), _hostname.c_str(), _hostname.size(), 0);
	// send(from->get_fd(), " 353 ", 5, 0);
	// send(from->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
	// send(from->get_fd(), " = #", 4, 0);
	// send(from->get_fd(), _name.c_str(), _name.size(), 0);
	// send(from->get_fd(), " :", 2, 0);
	// while (it != ite)
	// {
	// 	send(from->get_fd(), (*it)->get_nickname().c_str(), (*it)->get_nickname().size(), 0);
	// 	it++;
	// 	if (it != ite)
	// 		send(from->get_fd(), " ", 1, 0);
	// }
	// send(from->get_fd(), "\r\n", 2, 0);


	// send(from->get_fd(), ":", 1, 0);
	// send(from->get_fd(), _hostname.c_str(), _hostname.size(), 0);
	// send(from->get_fd(), " 366 ", 5, 0);
	// send(from->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
	// send(from->get_fd(), " #", 2, 0);
	// send(from->get_fd(), _name.c_str(), _name.size(), 0);
	// send(from->get_fd(), " :End of NAMES list", 19, 0);
	// send(from->get_fd(), "\r\n", 2, 0);

}

std::string Channel::get_hostname() const
{
	return (_hostname);
}


void Channel::change_hostname(const std::string &val)
{
	_hostname = val;
}