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

    (void)serv;
    args.str(arg);
    std::getline(args, name, ' ');
    cli->change_username(name);
    name.clear();

    std::getline(args, name, ' ');
    name.clear();

    std::getline(args, name, ' ');
    name.clear();
    put_operator(cli);

}