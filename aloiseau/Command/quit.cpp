#include "command.hpp"

void quit_cmd(Server *serv, Client *cli, std::string arg)
{
    std::string str = ":" + cli->get_nickname() + "!" + cli->get_username() + "@" + cli->get_hostname() + " QUIT " + arg + "\r\n";
    std::cout << "str quit est egal a :"<< str << std::endl;
    //throw std::runtime_error("Error while closing a connection.");
    send(cli->get_fd(), str.c_str(), str.length(), 0);
    serv->close_con(cli);
    //throw std::runtime_error("Error while closing a connection.");
}