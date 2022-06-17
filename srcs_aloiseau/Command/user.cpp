#include "command.hpp"

void user_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream                          args;
    std::string                                 name;

    args.str(arg);
    std::getline(args, name, ' ');
    // std::cout << "ici " << std::endl << name << std::endl;
    cli->change_username(name);
    name.clear();

    std::getline(args, name, ' ');
    // std::cout << name << std::endl;
    name.clear();

    std::getline(args, name, ' ');
    // std::cout << name << std::endl;
    cli->change_hostname(name);
    name.clear();

    //get_realname of client ??; take the next getline
    // std::getline(args, name, ' ');
}