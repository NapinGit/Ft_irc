#include "Server.hpp"

void signal_handler(int signal)
{
	(void)signal;
	std::cout << "CTRL-C catched" << std::endl ;

    throw std::runtime_error("Ctrl c detected");
}

int main(int ac, char **av)
{
	signal(SIGINT, &signal_handler);
    try 
    {
        if (ac != 3)
        {
            throw std::runtime_error("Usage: ./ircserv <port> <password>");
        }
        Server server_irc(av[1], av[2]);
        server_irc.start();
        
        return 0;
    }
    catch(const std::exception &exeption)
    {
        std::cerr << exeption.what() << std::endl;
        return 1;
    }
}