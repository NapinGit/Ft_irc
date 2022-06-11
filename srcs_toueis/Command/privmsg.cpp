#include "command.hpp"

void privmsg_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream      args;
    std::string             name;
    std::string             msg;

    std::map<std::string, Channel *>::iterator                                          it;

    args.str(arg);
    std::getline(args, name, ' ');
    std::cout << name << std::endl;
    
    //message to channel 
    //else: message to client
    if (name.c_str()[0] == '#')
    {
        name.erase(0, 1);
        it = serv->_channels.begin();
        std::getline(args, msg);
        msg.erase(0, 1);
        if (it != serv->_channels.end())
            it->second->send_to_chan(cli, msg);
    }
    else
    {
        
    }
}