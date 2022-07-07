#include "command.hpp"

void nick_cmd(Server *serv, Client *cli, std::string arg)
{
    std::map<int, Client *>::iterator it = serv->clients.begin();
    std::map<int, Client *>::iterator ite = serv->clients.end();
    if (cli->get_auth() == 0)
    {
        return;
    }
    if (cli->get_auth() && cli->get_nickname() != ""  && cli->get_hostname() != "")
    {
        std::string reply = ERR_ALREADYREGISTERED(cli->get_nickname());
        cli->send_to_client(reply);
    }
    if (arg.empty())
    {
        cli->change_auth(false);
        std::string reply = ERR_NONICKNAMEGIVEN(cli->get_nickname());
        cli->send_to_client(reply);
        return ;
    }
    if (arg != "")
    {
        while (it != ite)
        {
            if ((*it).second->get_nickname() == arg)
            {
                cli->change_auth(false);
                std::string reply = ERR_NICKNAMEINUSE(cli->get_nickname(), arg);
                cli->send_to_client(reply);
                return ;
            }
            it++;
        } 
        cli->change_nickname(arg);
    }
    else
    {
        cli->change_auth(false);
        std::string reply = ERR_NONICKNAMEGIVEN(cli->get_nickname());
        cli->send_to_client(reply);
    }
}