#include "command.hpp"

void kick_cmd(Server *serv, Client *cli, std::string arg)
{

    std::istringstream                          args;
    std::string chan_name;
    args.str(arg);
    std::getline(args, chan_name, ' ');
    

    chan_name = chan_name.substr(1 , chan_name.length());
    std::map<std::string, Channel *>::iterator it = serv->_channels.find(chan_name);
    if (it == serv->_channels.end())
    {
        std::string reply = ERR_NOSUCHCHANNEL(cli->get_nickname(), chan_name);
        cli->send_to_client(reply);
        return;
    }
    else
    {
        if (!(it->second->present_or_not_operators(cli)))
        {
            std::string reply = ERR_CHANOPRIVSNEEDED(cli->get_nickname(), chan_name);
            cli->send_to_client(reply);
            return;
        }
        std::vector<Client *>::iterator itv =  it->second->_clients.begin();
        std::vector<Client *>::iterator itev =  it->second->_clients.end();
        std::string kick_name;
        std::getline(args, kick_name, ' ');
        while (itv != itev)
        {
             if ((*itv)->get_nickname() == kick_name)
             {
                (*it).second->del(*itv);
                std::getline(args, kick_name);
                std::string reply = ":" + cli->get_nickname() + "!" + cli->get_username() +   "@" + cli->get_hostname() + " KICK #" + (*it).second->get_name() + " " + (*itv)->get_nickname() + " " + kick_name ;
                (*itv)->send_to_client(reply);
                (*itv)->del_chan(it->second);
                if (it->second->nb_clients() == 0)
                {
                    delete(it->second);
                    serv->_channels.erase(it);
                }
                return;
             }
            itv++;
        }
        std::string reply = "442 " + cli->get_nickname() + ": " + kick_name + " #" + chan_name +  " They are not on that channel";
		cli->send_to_client(reply);
    }
}