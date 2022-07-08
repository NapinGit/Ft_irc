#include "command.hpp"

void pass_cmd(Server *serv, Client *cli, std::string arg)
{
    if (cli->get_auth() == 1)
    {
        std::string reply = ERR_ALREADYREGISTERED(cli->get_nickname());
        cli->send_to_client(reply);
    }
    if (serv->get_password() == arg)
    {
        cli->change_auth(true);
    }
    else
    {
        std::string reply = ERR_PASSWDMISMATCH(cli->get_nickname());
        cli->send_to_client(reply);
    }
}