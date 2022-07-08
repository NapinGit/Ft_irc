#include "../include/Client.hpp"
#include <cstring>

class Channel;

Client::Client(const int &fd):
_auth(false), _operator(false), _nickname(""),  _username(""), _hostname(""), _fd(fd)
{}

Client::~Client()
{}

int Client::get_fd() const
{
    return(_fd);
}

void Client::add_channel(Channel *chan)
{
    _channels.insert(std::make_pair(chan->get_name(), chan));
}

std::string Client::get_username() const
{
    return (_username);
}

std::string Client::get_nickname() const
{
    return (_nickname);
}

std::string Client::get_hostname() const
{
    return (_hostname);
}

bool Client::get_auth() const
{
    return (_auth);
}

bool Client::get_operator() const
{
    return (_operator);
}

pollfd Client::get_pollfd() const
{
    return (_pollfd);
}

void Client::change_auth(bool val)
{
    _auth = val;
}

void Client::change_nickname(std::string &val)
{
    _nickname = val;
}

void Client::change_username(std::string &val)
{
    _username = val;
}

void Client::change_hostname(std::string &val)
{
    _hostname = val;
}

void Client::change_operator(bool val)
{
    _operator = val;
}

void Client::send_to_client(std::string &msg)
{
    std::string buffer = msg + "\r\n";
	if (send(_fd, buffer.c_str(), buffer.length(), 0) < 0)
		throw std::runtime_error("Error while sending message to client.");
}

void Client::del_chan(Channel *ptr)
{
    _channels.erase(ptr->get_name());
}