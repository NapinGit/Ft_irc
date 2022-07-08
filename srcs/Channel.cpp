#include "Channel.hpp"

template<class InputIterator, class T>
InputIterator find (InputIterator first, InputIterator last, const T& val)
{
	while (first != last) 
	{
		if (*first == val)
			return first;
		++first;
	}
	return last;
}

Channel::Channel(std::string name, Client *cli): _name(name) , _key(""), _secure(0)
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
		del_operator(cli);
		_clients.erase(find(_clients.begin(), _clients.end(), cli));
	}
}

void Channel::leave_msg(Channel *chan, Client *cli, std::string arg)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();

	while (it != ite)
	{
		std::string reply = ":" + cli->get_nickname() + "!" + cli->get_username() + "@" + cli->get_hostname() + " PART #" + chan->get_name() + " " + arg;
		(*it)->send_to_client(reply);
		it++;
	}
}

void Channel::rpl_kick(Channel *chan, Client *cli, std::string arg)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();

	while (it != ite)
	{
		std::string reply = ":" + cli->get_nickname() + "!" + cli->get_username() + "@" + cli->get_hostname() + " PART #" + chan->get_name() + " " + arg;
		(*it)->send_to_client(reply);
		it++;
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
		_operators.erase(find(_operators.begin(), _operators.end(), cli));
}

size_t Channel::nb_clients()
{
	std::vector<Client *>::iterator 	it = _clients.begin();
	std::vector<Client *>::iterator 	ite = _clients.end();
	size_t 								nb;

	nb = 0;
	for(nb = 0; it != ite; it++, nb++)
	{}
	std::cout << "nb of clients on channel #" << get_name() << " " << nb << std::endl;
	return nb;
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
			std::string str = ":" + from->get_nickname() + " PRIVMSG #" + _name + " :" + msg + "\r\n";
			send((*it)->get_fd(), str.c_str(), str.length(), 0);
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
		it++;
	}
}

void Channel::rpl_namreply(Client *from)
{
	std::vector<Client *>::iterator it = _clients.begin();
	std::vector<Client *>::iterator ite = _clients.end();
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
	list.clear();
	list = ":" + _hostname + " 366 " + from->get_nickname() + " #" + _name +  " :End of NAMES list\r\n";
	send(from->get_fd(), list.c_str(), list.length(), 0);
}

std::string Channel::get_hostname() const
{
	return (_hostname);
}


void Channel::change_hostname(const std::string &val)
{
	_hostname = val;
}

std::string Channel::get_key() const
{
	return(_key);
}

void Channel::change_key(std::string key)
{
	_key = key;
}

bool Channel::is_secure() const
{
	return(_secure);
}

void Channel::change_secure(bool monbool)
{
	_secure = monbool;
}

Client	*Channel::find_client(std::string client)
{
	std::vector<Client *>::iterator it;
	std::vector<Client *>::iterator ite;

	it = _clients.begin();
	ite = _clients.end();

	while (it != ite)
	{
		if ((*it)->get_nickname() == client)
			return ((*it));
		it++;
	}
	return (NULL);
}