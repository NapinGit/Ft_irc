#include "command.hpp"

//decoupage arg pour aovir le commentaire et code erreur a renvoyer

void kick_cmd(Server *serv, Client *cli, std::string arg)
{
    // faire un check si le cli est oprateur


    //std::string chan_name = arg.substr(1 , arg.find(" ") - 1);
    std::istringstream                          args;
    std::string chan_name;
    args.str(arg);
    std::getline(args, chan_name, ' ');
    
    //arg = arg + arg.find(" ");
	//std::map<int, Client *>::iterator ite = serv->clients.end();
    chan_name = chan_name.substr(1 , chan_name.length());
    // std::cout << "chan name : |" << chan_name << "|end"<< std::endl;
    std::map<std::string, Channel *>::iterator it = serv->_channels.find(chan_name);
    if (it == serv->_channels.end())
    {
        std::cout << "chan not found" << std::endl;
        //chan not found
    }
    else
    {
        std::vector<Client *>::iterator itv =  it->second->_clients.begin();
        std::vector<Client *>::iterator itev =  it->second->_clients.end();
        //decoupage foireux pour le moment;
        //std::string kick_name = arg.substr(arg.find(" ") + 1, arg.find(":") - 1);
        std::string kick_name;
        std::getline(args, kick_name, ' ');
        while (itv != itev)
        {

            // std::cout << "ite on client = : |" << (*itv)->get_nickname() << "|\n";
            if ((*itv)->get_nickname() == kick_name)
            {
                // std::cout << "Client found : |" << kick_name << "|\n";
                (*it).second->del(*itv);
                std::getline(args, kick_name);
                std::string reply = ":" + cli->get_nickname() + "!" + cli->get_username() +   "@" + cli->get_hostname() + " KICK #" + (*it).second->get_name() + " " + (*itv)->get_nickname() + " " + kick_name ; 
                //  std::string reply = ":" + cli->get_nickname() + " KICK #" + (*it).second->get_name() + " " + (*itv)->get_nickname() + " " + kick_name ; 
                (*itv)->send_to_client(reply);
                //virer le client du chan
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
        std::cout << "Client not found : |" << kick_name << "|\n";
    }
    

}