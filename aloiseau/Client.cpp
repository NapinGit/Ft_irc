#include "Client.hpp"
#include <cstring>

class Channel;

Client::Client(const int &fd):
_auth(false), _operator(false), _nickname(""),  _username(""), _hostname(""), _fd(fd)
{

}

Client::~Client()
{

}

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

void Client::send_to_client(Client *from, const char *msg)
{
    send(_fd, ":", 1, 0);
    send(_fd, from->get_nickname().c_str(), from->get_nickname().size(), 0);
    send(_fd, " PRIVMSG ", 9, 0);
    send(_fd, _nickname.c_str(), _nickname.size(), 0);
    send(_fd, " :", 2, 0);
    send(_fd, msg, std::strlen(msg), 0);
    send(_fd, "\r\n", 2, 0);
}

void Client::send_to_client(Client *from, const std::string msg)
{
    send(_fd, ":", 1, 0);
    send(_fd, from->get_nickname().c_str(), from->get_nickname().size(), 0);
    send(_fd, " PRIVMSG ", 9, 0);
    send(_fd, _nickname.c_str(), _nickname.size(), 0);
    send(_fd, " :", 2, 0);
    send(_fd, msg.c_str(), msg.size(), 0);
    send(_fd, "\r\n", 2, 0);
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
    // std::string name = ptr->get_name();

    // std::map<std::string , Channel *>::iterator it = find(_channels.begin(), _channels.end(), ptr);
}