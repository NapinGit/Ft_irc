#include "Client.hpp"

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

std::string Client::get_user() const
{
    return (_user);
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
    _username = val;
}

