#include "Server.hpp"

int main(int ac, char **av)
{
    try 
    {
        if (ac != 3)
        {
            throw std::runtime_error("Usage: ./ircserv <port> <password>");
        }
        Server Server(av[1], av[2]);
        return 0;
    }
    catch(const std::exception &exeption)
    {
        std::cerr << exeption.what() << std::endl;
        return 1;
    }
}