#include "command.hpp"

void put_operator(Client *cli)
{
    if (cli->get_username() == "aloiseau" || cli->get_username() == "toueis")
    {
        cli->change_operator(1);
    }
}

void user_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream                          args;
    std::string                                 name;

    std::cout << "mon test2 user ? = " << arg << std::endl;

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
    // cli->change_hostname(name);
    name.clear();
    put_operator(cli);

    //get_realname of client ??; take the next getline
    // std::getline(args, name, ' ');
}