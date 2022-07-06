#include "command.hpp"

void join_cmd(Server *serv, Client *cli, std::string arg)
{
	std::istringstream                                                                  buffer;
    std::istringstream                                                                  bloc;
    std::string                                                                         chans;
    std::string                                                                         chan;
    // std::string                                                                         keys;
    // std::string                                                                         key;
    std::map<std::string, Channel *>::iterator                                          it;

    //getline necessite un inputstream
    buffer.str(arg);

    //arg sous forme (tout ce qui est entre [] est optionnel)--->      JOIN channel1[,channel2,channel3,...] [password1,password2,password3,...]
    //Decoupe en 2 blocs, le premier de channels et le deuxieme de passwords
    std::getline(buffer, chans, ' ');

    //travaillle sur le premier bloc, a splitter par des ',' pour obternir la list des channels
    //getline necessite un inputstream
    bloc.str(chans);
    //split par ','
    while (std::getline(bloc, chan, ','))
    {
        chan.erase(0,1);
        // std::cout << "channel = " << chan << std::endl;
        if ((serv->_channels).find(chan) == (serv->_channels).end())
        {
            std::cout << "create new channel" << std::endl;
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
                    std::string reply = "475 " + cli->get_nickname() + " #" + chan + " :Blabla";
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

    //gestion des passwd
    std::getline(buffer, chans, ' ');
    while (std::getline(bloc, chan, ','))
    {
            //gerer les passwd d'aut pour les channel aproprié
    }
}