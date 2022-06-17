#include "command.hpp"

void pass_cmd(Server *serv, Client *cli, std::string arg)
{
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