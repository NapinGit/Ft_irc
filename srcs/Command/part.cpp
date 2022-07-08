#include "command.hpp"

void part_cmd(Server *serv, Client *cli, std::string arg)
{
    std::string chan = arg.substr(1, arg.length());
    std::map<std::string, Channel *>::iterator it= serv->_channels.find(chan);
    
    if (it != serv->_channels.end())
    {
        it->second->del(cli);
        cli->del_chan(it->second);
        std::string reply = ":" + cli->get_nickname() + "!" + cli->get_username() +   "@" + cli->get_hostname() + " PART " + arg  ;
        cli->send_to_client(reply);
        it->second->leave_msg(it->second, cli, arg);
    }
    else
    {
        std::string reply = ERR_NOTONCHANNEL(arg);
        cli->send_to_client(reply);
    }
}