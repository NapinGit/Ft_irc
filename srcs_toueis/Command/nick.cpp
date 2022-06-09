#include "command.hpp"

void nick_cmd(Server *serv, Client *cli, std::string arg)
{
    if (arg != "")
    {
        cli->change_nickname(arg);
         std::cout << "nick = "<< arg << std::endl;
    }
    else
    {
        cli->change_auth(false);
    }

}