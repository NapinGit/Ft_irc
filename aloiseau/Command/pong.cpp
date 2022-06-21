#include "command.hpp"

void pong_cmd(Server *serv, Client *cli, std::string arg)
{
    (void)serv;
    send(cli->get_fd(), ":", 1, 0);
    send(cli->get_fd(), cli->get_nickname().c_str(), cli->get_nickname().size()-1, 0);
    send(cli->get_fd(), " PONG :", 9, 0);
    send(cli->get_fd(), " :", 2, 0);
    send(cli->get_fd(), arg.c_str(), arg.size(), 0);
    send(cli->get_fd(), "\r\n", 2, 0);
}