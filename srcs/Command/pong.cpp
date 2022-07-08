#include "command.hpp"

void pong_cmd(Server *serv, Client *cli, std::string arg)
{
    (void)serv; 
    std::string reply = ":" + cli->get_nickname() + " PONG : :" + arg;
    cli->send_to_client(reply);
}