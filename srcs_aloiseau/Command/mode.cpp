#include "command.hpp"

void mode_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream      args;
    std::string             mode;
    std::string             msg;

    std::map<std::string, Channel *>::iterator                                          it;

    args.str(arg);
    std::getline(args, mode, ' ');
    // std::cout << mode << std::endl;
    if (mode.c_str()[0] == '#')
    {
        mode.erase(0,1);
        std::string str = ":" + serv->get_hostname() + " 324 " + cli->get_nickname() + mode + " +i\r\n";
        // std::cout << str;
        // send(cli->get_fd(), str.c_str(), str.size(), 0);

    }
    else
        NULL;
}