#include "command.hpp"

void user_cmd(Server *serv, Client *cli, std::string arg)
{
    if (arg != "")
    {
        std::string result = arg.substr(arg.find(" "), arg.length());
        cli->change_username(result);
    }
}