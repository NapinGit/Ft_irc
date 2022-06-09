#include "Client.hpp"
#include <cstring>

class Channel;

Client::Client(const int &fd):
_auth(false), _operator(false), _nickname(""), _user(""), _fd(fd)
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

std::string Client::get_user() const
{
    return (_user);
}

void Client::send_to_client(Client *from, const char *msg)
{
    std::cout << "msg:" << msg << std::endl;
    send(_fd, ":", 1, 0);
    send(_fd, from->get_nickname().c_str(), _nickname.size()-1, 0);
    send(_fd, " PRIVMSG ", 9, 0);
    send(_fd, _nickname.c_str(), _nickname.size(), 0);
    send(_fd, " :", 2, 0);
    send(_fd, msg, std::strlen(msg), 0);
    send(_fd, "\r\n", 2, 0);
}

void Client::send_to_client(Client *from, const std::string msg)
{
    std::cout << "msg:" << msg.c_str() << std::endl;
    send(_fd, ":", 1, 0);
    send(_fd, from->get_nickname().c_str(), _nickname.size()-1, 0);
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

bool Client::get_auth() const
{
    return (_auth);
}

bool Client::get_operator() const
{
    return (_operator);
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
    _user = val;
}

