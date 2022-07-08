#include "command.hpp"

void join_cmd(Server *serv, Client *cli, std::string arg)
{
	std::istringstream                                                                  buffer;
    std::istringstream                                                                  bloc;
    std::string                                                                         chans;
    std::string                                                                         chan;
    std::map<std::string, Channel *>::iterator                                          it;

    buffer.str(arg);
    std::getline(buffer, chans, ' ');
    bloc.str(chans);
    while (std::getline(bloc, chan, ','))
    {
        chan.erase(0,1);
        if ((serv->_channels).find(chan) == (serv->_channels).end())
        {
            std::cout << "Create new channel with name " << chan << std::endl;
            Channel *c = new Channel(chan, cli);
            c->add(cli);
            c->add_operator(cli);
            c->change_hostname(serv->get_hostname());
            cli->add_channel(c);
            serv->_channels.insert(std::make_pair(chan, c));
            c->rpl_join(cli);
            c->rpl_namreply(cli);
        }
        else
        {
            it = (serv->_channels).find(chan);
            if(it->second->is_secure())
            {
                std::string key;
                std::getline(buffer, key, ' ');
                if (!(it->second->get_key() == key))
                {
                    //PASS DISMATCH
                    std::string reply = "475 " + cli->get_nickname() + " #" + chan + " :Chan password dismatch";
                    cli->send_to_client(reply);
                    return;
                }
            }
            std::cout << "add new user to channel " << chan << std::endl;
            (it->second)->add(cli);
            cli->add_channel((it->second));
            (it->second)->rpl_join(cli);
            (it->second)->rpl_namreply(cli);
        }
    }
    bloc.clear();
}