#include "command.hpp"

void nick_cmd(Server *serv, Client *cli, std::string arg)
{
    std::map<int, Client *>::iterator it = serv->clients.begin();
    std::map<int, Client *>::iterator ite = serv->clients.end();

    if (arg != "")
    {
        while (it != ite)
        {
            if ((*it).second->get_nickname() == arg)
            {
                cli->change_auth(false);
                return ;
            }
            it++;
        }
        cli->change_nickname(arg);
    }
    else
    {
        cli->change_auth(false);
    }
}