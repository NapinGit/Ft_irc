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

std::string Channel::get_name()
{
	return (_name);
}

void Channel::send_to_chan(Client *from, std::string msg)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();

	while (it != ite)
	{
		(*it)->send_to_client(from, msg);
		it++;
	}
}