#include "command.hpp"

void invite_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream                          args;
    std::string                                 nickname;
    std::string                                 channel;

    (void)serv;
    args.str(arg);
    std::getline(args, nickname, ' ');
    std::getline(args, channel, ' ');
    channel.erase(0, 1);
    std::string str = ":" + cli->get_nickname() + " INVITE #" + nickname + " " + channel + "\r\n";
    
    std::map<int , Client *>::iterator it = serv->clients.begin();
    std::map<int , Client *>::iterator ite = serv->clients.end();
    while (it != ite)
    {
        if (it->second->get_nickname() == nickname)
            break;
        it++;
    };
    if (it != ite)
        send(it->second->get_fd(), str.c_str(), str.length(), 0);
}