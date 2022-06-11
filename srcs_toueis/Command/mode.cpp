#include "command.hpp"

void mode_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream      args;
    std::string             mode;
    std::string             msg;

    std::map<std::string, Channel *>::iterator                                          it;

    args.str(arg);
    std::getline(args, mode, ' ');
    std::cout << mode << std::endl;
}