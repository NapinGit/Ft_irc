#include "command.hpp"

void mode_cmd(Server *serv, Client *cli, std::string arg)
{
    std::istringstream      args;
    std::string             mode;
    std::string             target;
    std::string             msg;

    std::map<std::string, Channel *>::iterator                                          it;

    args.str(arg);
    std::getline(args, target, ' ');
    // std::cout << target << std::endl;
    if (target.c_str()[0] == '#')
    {
        target.erase(0, 1);
        it = (serv->_channels).find(target);
        if (it == serv->_channels.end())
        {
            //RPL ERR NO CHANN FOUND
            return;
        }
        std::getline(args, mode, ' ');
        if (mode.c_str()[0] == '+')
        {
            if (mode.c_str()[1] == 'i')
            {

            }
            else if (mode.c_str()[1] == 'o')
            {

            }
            else if (mode.c_str()[1] == 'k')
            {
                if (it->second->present_or_not_operators(cli))
                {
                    std::cout << "ici" << std::endl;
                    std::string      pass;
                    std::getline(args, pass, ' ');
                    if (pass.length() != 0)
                    {
                        it->second->change_key(pass);
                        it->second->change_secure(true);
                    }
                    else
                        //RPL PASS EMPTY ERROR ??
                    return ;
                }
                else
                {
                    //RPL ERR YOU R NOT OPERATOR
                }
            }
        }
        else
        {
            if (mode.c_str()[1] == 'i')
            {

            }
            else if (mode.c_str()[1] == 'o')
            {

            }
            else if (mode.c_str()[1] == 'k')
            {
                if (it->second->present_or_not_operators(cli))
                {
                    it->second->change_key("");
                    it->second->change_secure(false);
                    return ;
                }
                else
                {
                    //RPL ERR YOU R NOT OPERATOR
                }
            }
        }
    }
    else
        NULL;
}
//        target.erase(0,1);
        // std::string str = ":" + serv->get_hostname() + " 324 " + cli->get_nickname() + mode + " +i\r\n";
        // std::cout << str;
        // send(cli->get_fd(), str.c_str(), str.size(), 0);