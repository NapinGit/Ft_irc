#include "command.hpp"

void user_cmd(Server *serv, Client *cli, std::string arg)
{
    if (arg != "")
    {
        std::string result = arg.substr(0 , arg.find(" "));
        cli->change_username(result);
         std::cout << "user = "<< result << std::endl;
    }
    /*else
    {
        std::string reply = ERR_NONICKNAMEGIVEN(arg);
        cli->send_to_client(reply);
        return ;
    }*/
}