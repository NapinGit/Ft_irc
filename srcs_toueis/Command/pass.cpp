#include "command.hpp"

void pass_cmd(Server *serv, Client *cli, std::string arg)
{
    // if (serv->get_password() == arg)
    // {
        cli->change_auth(true);
        // std::cout << "pass = "<< arg << std::endl;
    // }
    // else
    // {
        //error password does not match
    // }
}