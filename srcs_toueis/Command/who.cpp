#include "command.hpp"

void who_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream      args;
    std::string             argument;
    std::string             msg;

    std::map<std::string, Channel *>::iterator                                          it;

    args.str(arg);
    std::getline(args, argument, ' ');
    if (argument.c_str()[0] == '#')
    {
        // argument.erase(0,1);
        // std::string str = "352 " + cli->get_nickname() + " " + argument + " " + cli->get_username() + " " + cli->get_hostname() + " " + serv->get_hostname() + " " + cli->get_nickname() + " ";
        // std::string str = "315 " + cli->get_nickname() + " " + argument + " " + cli->get_username() + " " + cli->get_hostname() + " " + serv->get_hostname() + " " + cli->get_nickname() + " ";
        
         
        //  str = str + "\r\n";
        
        // std::cout << str;
        // send(cli->get_fd(), str.c_str(), str.size(), 0);

    }
    else
        NULL;
}