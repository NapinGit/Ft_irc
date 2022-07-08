#include "command.hpp"

void cap_cmd(Server *serv, Client *cli, std::string arg)
{
    (void)serv;
    if (arg == "LS")
        send(cli->get_fd(), "CAP * LS :\r\n", 12, 0);
    else if (arg == "END")
    {
        if (cli->get_auth() == 1)
        {
            std::string str = "001 " + cli->get_nickname() + " Welcome to my Internet Relay 42Network\r\n";
         	send(cli->get_fd(), str.c_str(), str.length(), 0);
            std::cout << "New client connected with nickname :" << cli->get_nickname() << std::endl;
        }
        else
        {
            
         	send(cli->get_fd(), "Error auth\r\n", 12, 0);
            serv->close_con(cli);
        }
    }
}