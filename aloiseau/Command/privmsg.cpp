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
    std::cout << "name is" << name << std::endl;
    if (name.c_str()[0] == '#')
    {
        std::cout << "name is if" << name << std::endl;
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
        std::cout << "name is else" << name << std::endl;
        itclient = serv->clients.begin();
        itcliente = serv->clients.end();
        //cherche le client sil existe 
        std::cout << "name is elscqcqcqe" << name << std::endl;
        while (itclient->second->get_nickname() != name && itclient != itcliente)
            itclient++;
             std::cout << "name is elsearaaeagezgergregehrehc" << name << std::endl;
        //sil nexiste pas, RPL ERR PRIVMSG ??
        if (itclient == itcliente)
        {
            return ;
        }
        std::cout << "name is elsearaaeagezgergregehrehc" << name << std::endl;
        //envoi du message au client destinataire (itclient)
        std::getline(args, msg);
        std::string str;
        str = ":" + cli->get_nickname() + "!" + cli->get_username() + "@" + cli->get_hostname() + " PRIVMSG " + itclient->second->get_nickname() + " " + msg + "\r\n";
        send(itclient->second->get_fd(), str.c_str(), str.length(), 0);
        std::cout << "name is elscqcqcqe" << name << std::endl;
    }
    std::cout << name << std::endl;
}