#include "command.hpp"

void privmsg_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream      args;
    std::string             name;
    std::string             msg;

    std::map<std::string, Channel *>::iterator                                          itchan;
    std::map<int, Client *>::iterator                                                   itclient;
    std::map<int, Client *>::iterator                                                   itcliente;

    args.str(arg);
    std::getline(args, name, ' ');
    //std::cout << name << std::endl;
    
    //message to channel 
    //else: message to client
    if (name.c_str()[0] == '#')
    {
        name.erase(0, 1);
        //cherche si le cannal existe
        itchan = serv->_channels.find(name);
        std::getline(args, msg);
        msg.erase(0, 1);
        //envoi le message a tout le cannal s'il existe
        if (itchan != serv->_channels.end())
            itchan->second->send_to_chan(cli, msg);
    }
    else
    {
        itclient = serv->clients.begin();
        itcliente = serv->clients.end();
        //cherche le client sil existe 
        while ( itclient != itcliente && itclient->second->get_nickname() != name )
            itclient++;
        //sil nexiste pas, RPL ERR PRIVMSG ??
        if (itclient == itcliente)
        {
            std::string reply = "401 " + cli->get_nickname() /*+ " :No such nick/channel"*/ ;
            cli->send_to_client(reply);
            return ;
        }
        //envoi du message au client destinataire (itclient)
        std::getline(args, msg);
        std::string str;
        str = ":" + cli->get_nickname() + "!" + cli->get_username() + "@" + cli->get_hostname() + " PRIVMSG " + itclient->second->get_nickname() + " " + msg + "\r\n";
        send(itclient->second->get_fd(), str.c_str(), str.length(), 0);
    }
    std::cout << name << std::endl;
}