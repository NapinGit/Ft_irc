#include "command.hpp"

void quit_cmd(Server *serv, Client *cli, std::string arg)
{
    std::string str = ":" + cli->get_nickname() + " QUIT :Quit: " + arg;
    cli->send_to_client(str);
    serv->close_con(cli);
}