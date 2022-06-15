#include "command.hpp"

void who_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream      args;
    std::string             argument;
    std::string             msg;

    std::map<std::string, Channel *>::iterator                                          it;

    //WHO <USER> response
    // :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat emersion H :1 Simon Ser

    //WHO <CHAN> response
    // :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat emersion H :1 Simon Ser
    // :calcium.libera.chat 352 dan #ircv3 ~val limnoria/val calcium.libera.chat val H :1 Val
    args.str(arg);
    std::getline(args, argument, ' ');
    if (argument.c_str()[0] == '#')
    {
           //WHO <CHAN> response
            // :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat emersion H :1 Simon Ser
            // :calcium.libera.chat 352 dan #ircv3 ~val limnoria/val calcium.libera.chat val H :1 Val

            //end
        //   :calcium.libera.chat 315 dan #ircv3 :End of WHO list

        argument.erase(0,1);
        it = serv->_channels.find(argument);
        //CHANNEL NEXISTE PAS ? RPL ERROR ?
        if (it == serv->_channels.end())
            return ;
        // it->second->_clients.begin();
        std::string str = ":" + cli->get_hostname() +  " 352 " + cli->get_nickname() + " #" + argument + " " + cli->get_username() + " " + cli->get_hostname() + " " + serv->get_hostname() + " " + cli->get_nickname() + " H";
        if (it->second->present_or_not_operators(cli))
            str = str + "@";
        str = str + " :0 " + cli->get_username() + "\r\n";
        send(cli->get_fd(), str.c_str(), str.size(), 0);
        
        str.clear();
        str = ":" + cli->get_hostname() +  " 315 " + cli->get_nickname() + " #" + argument + " :End of WHO list\r\n";
        // std::string str = "315 " + cli->get_nickname() + " " + argument + " " + cli->get_username() + " " + cli->get_hostname() + " " + serv->get_hostname() + " " + cli->get_nickname() + " ";
        
         
        //  str = str + "\r\n";
        
        // std::cout << str;
        // send(cli->get_fd(), str.c_str(), str.size(), 0);

    }
    else
        NULL;
}