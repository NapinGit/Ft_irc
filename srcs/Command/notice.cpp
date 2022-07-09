#include "../../include/command.hpp"

void notice_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream                          args;
    std::string                                 name;
    std::string                                 msg;
    std::map<std::string, Channel *>::iterator  itchan;
    std::map<int, Client *>::iterator           itclient;
    std::map<int, Client *>::iterator           itcliente;

    args.str(arg);
    std::getline(args, name, ' ');
    if (name.c_str()[0] == '#')
    {
        name.erase(0, 1);
        itchan = serv->_channels.find(name);
        std::getline(args, msg);
        msg.erase(0, 1);
        if (itchan != serv->_channels.end() && itchan->second->present_or_not(cli))
            itchan->second->send_to_chan_notice(cli, msg);
    }
    else
    {
        itclient = serv->clients.begin();
        itcliente = serv->clients.end();
        while (itclient != itcliente && itclient->second->get_nickname() != name)
            itclient++;
        if (itclient == itcliente)
            return ;
        std::getline(args, msg);
        std::string str;
        str = ":" + cli->get_nickname() + "!" + cli->get_username() + "@" + cli->get_hostname() + " NOTICE " + itclient->second->get_nickname() + " " + msg + "\r\n";
        send(itclient->second->get_fd(), str.c_str(), str.length(), 0);
    }
    std::cout << name << std::endl;
}