#include "Client.hpp"

Client::Client(const std::string &nickname, const std::string &user,const int &fd):
_nickname(nickname), _user(user), _fd(fd)
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

