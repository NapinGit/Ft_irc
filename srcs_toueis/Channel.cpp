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

void Channel::add(Client *cli)
{
	if (!present_or_not(cli))
		_clients.push_back(cli);
}

void Channel::del(Client *cli)
{
	std::vector<Client *>::iterator it = find(_clients.begin(), _clients.end(), cli);

	if (it != _clients.end())
		_clients.erase(find(_clients.begin(), _clients.end(), cli));
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
	        std::cout << "ARG" << from->get_nickname() <<  std::endl;
			send((*it)->get_fd(), ":", 1, 0);
			send((*it)->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
			send((*it)->get_fd(), " PRIVMSG #", 10, 0);
			send((*it)->get_fd(), _name.c_str(), _name.size(), 0);
			send((*it)->get_fd(), " :", 2, 0);
			send((*it)->get_fd(), msg.c_str(), msg.size(), 0);
			send((*it)->get_fd(), "\r\n", 2, 0);
		}
		it++;
	}
}

void Channel::rpl_join(Client *from)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();

	// rpl_namreply(from);
	while (it != ite)
	{
		// if ((*it) != from)
		// {
			send((*it)->get_fd(), ":", 1, 0);
			send((*it)->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
			send((*it)->get_fd(), "!", 1, 0);
			send((*it)->get_fd(), from->get_username().c_str(), from->get_nickname().size(), 0);
			send((*it)->get_fd(), "@", 1, 0);
			send((*it)->get_fd(),  from->get_hostname().c_str(), from->get_hostname().size(), 0);
			send((*it)->get_fd(), " JOIN #", 7, 0);
			send((*it)->get_fd(), _name.c_str(), _name.size(), 0);
			send((*it)->get_fd(), "\r\n", 2, 0);
		// }
		it++;
	}
}

void Channel::rpl_namreply(Client *from)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();

//topic reply
	send(from->get_fd(), ":", 1, 0);
	send(from->get_fd(), _hostname.c_str(), _hostname.size(), 0);
	send(from->get_fd(), " 332 ", 5, 0);
	send(from->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
	send(from->get_fd(), " #", 2, 0);
	send(from->get_fd(), _name.c_str(), _name.size(), 0);
	send(from->get_fd(), " :", 2, 0);
	send(from->get_fd(), "TOPIC", 5, 0);
	send(from->get_fd(), "\r\n", 2, 0);

//list of user on channel rpl and endoflist
	send(from->get_fd(), ":", 1, 0);
	send(from->get_fd(), _hostname.c_str(), _hostname.size(), 0);
	send(from->get_fd(), " 353 ", 5, 0);
	send(from->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
	send(from->get_fd(), " = #", 4, 0);
	send(from->get_fd(), _name.c_str(), _name.size(), 0);
	send(from->get_fd(), " :@", 3, 0);
	while (it != ite)
	{
		send(from->get_fd(), (*it)->get_nickname().c_str(), (*it)->get_nickname().size(), 0);
		it++;
		if (it != ite)
			send(from->get_fd(), " ", 1, 0);
	}
	send(from->get_fd(), "\r\n", 2, 0);
	send(from->get_fd(), ":", 1, 0);
	send(from->get_fd(), _hostname.c_str(), _hostname.size(), 0);
	send(from->get_fd(), " 366 ", 5, 0);
	send(from->get_fd(), from->get_nickname().c_str(), from->get_nickname().size(), 0);
	send(from->get_fd(), " #", 2, 0);
	send(from->get_fd(), _name.c_str(), _name.size(), 0);
	send(from->get_fd(), " :End of NAMES list", 19, 0);
	send(from->get_fd(), "\r\n", 2, 0);

}

std::string Channel::get_hostname() const
{
	return (_hostname);
}


void Channel::change_hostname(const std::string &val)
{
	_hostname = val;
}