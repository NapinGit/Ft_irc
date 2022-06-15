#include "command.hpp"

void nick_cmd(Server *serv, Client *cli, std::string arg)
{
    if (arg != "")
    {
        cli->change_nickname(arg);
        //  std::cout << "nick = "<< arg << std::endl;
        // std::string str = ": NICK " + cli->get_nickname() + "\r\n";
        // send(cli->get_fd(), str.c_str(), str.length(), 0);
        //  std::cout << str << std::endl;

    }
    else
    {
        cli->change_auth(false);
    }

}