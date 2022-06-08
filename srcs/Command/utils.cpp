# include <istream>
# include <sstream>
# include <iostream>
# include <cstring>
# include <map>

void    dec_buff(char *buff)
{
    std::istringstream                                                                  buffer;
    std::istringstream                                                                  l;
    std::string                                                                         line;
    std::string                                                                         cmdd;
    std::string                                                                         arg;
    std::map<std::string, void (*)(Server *serv, Client *cli, std::string arg)>::iterator     it;

    buffer.str(buff);
    while(std::getline(buffer, line))
    {
        l.str(line);
        std::getline(l, cmdd, ' ');
        std::cout << "CMDd " << cmdd <<  std::endl;
        std::getline(l, arg);
        std::cout << "ARG " << arg <<  std::endl;
        it = cmd.find(cmdd);
        (it->second)(*this, )
        l.clear();
    }
}