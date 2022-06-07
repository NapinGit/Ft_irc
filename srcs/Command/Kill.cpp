#include "command.hpp"

void kiall(t_irc *obj, int fd, char *arg)
{
	std::cout << "coucou \n" << obj->_port << std::endl;
}