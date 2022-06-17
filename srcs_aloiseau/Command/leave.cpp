#include "command.hpp"

void leave_cmd(Server *serv, Client *cli, std::string arg)
{
    std::string result = arg.substr(1 , arg.find(" "));
    std::cout << "arg = " << result << std::endl;
    cli->change_username(result);
    if (cli->_channels.empty())
    {
        return;
        // no channel joined
    }
    // std::map<std::string , Channel *> ::iterator it = cli->_channels.begin();
    // std::map<std::string , Channel *> ::iterator ite = cli->_channels.end();
    std::map<std::string , Channel *> ::iterator it = cli->_channels.find(result);
    if (it == cli->_channels.end())
    {
        //channel not joined or not created
        return;
    }
    else
    {
        std::vector<Client *> vec = it->second->get_client();
         std::vector<Client *>::iterator vecit = it->second->get_client().begin();
         std::vector<Client *>::iterator vecite = it->second->get_client().end();
         Client *yolo = *vecit;
         while (vecit != vecite)
         {
            yolo = *vecit;
            if (cli->get_nickname() == yolo->get_nickname())
            {
                //remove client from list;
                vec.erase(vecit);
                cli->_channels.erase(it);
                break;
                NULL;
            }
            vecit++;
         }
                
    }

    serv->_channels;
}