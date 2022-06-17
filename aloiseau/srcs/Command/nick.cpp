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
        std::string reply = ERR_NONICKNAMEGIVEN(arg);
        cli->send_to_client(reply);
        cli->change_auth(false);
        return ;
    }

}