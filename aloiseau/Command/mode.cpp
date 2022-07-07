#include "command.hpp"

void mode_cmd(Server *serv, Client *cli, std::string arg)
{
	std::istringstream      args;
	std::string             mode;
	std::string             target;
	std::string             msg;

	std::map<std::string, Channel *>::iterator  it;

	args.str(arg);
	std::getline(args, target, ' ');
	std::getline(args, mode, ' ');
	// std::cout << target << std::endl;
	if (target.c_str()[0] == '#')
	{
		target.erase(0, 1);
		it = (serv->_channels).find(target);
		if (mode.length() == 0)
		{
			//CLIENT ASK MODE FROM CHAN
			return;
		}
		if (it == serv->_channels.end())
		{
			//RPL ERR NO CHANN FOUND
			std::cout << "ERR CHAN NOT FIND" << std::endl;
			std::string reply = "403 #" + target + " :#" + target;
			cli->send_to_client(reply);
			return;
		}
		if (!it->second->present_or_not(cli))
		{
			//RPL ERR NOT OPERATOR
			std::cout << "ERR U R NOT ON CHAN" << std::endl;
			std::string reply = "442 #" + target + " :You're not on channel";
			cli->send_to_client(reply);
			return;
		}
		if (!it->second->present_or_not_operators(cli))
		{
			//RPL ERR NOT OPERATOR
			std::cout << "ERR U R NOT OP" << std::endl;
			std::string reply = "482 #" + target + " :You're not channel operator";
			cli->send_to_client(reply);
			return;
		}


		if (mode.c_str()[0] == '+')
		{
			if (mode.c_str()[1] == 'i')
			{
				
			}
			else if (mode.c_str()[1] == 'o')
			{
				std::cout << "Mode CHAN +o" << std::endl;
				std::string      user;
				std::getline(args, user, ' ');
				Client *ref;

				ref = it->second->find_client(user);
				if (ref != NULL)
				{
					std::cout << "CLI ADDED TO OPERATORS" << std::endl;
					it->second->add_operator(ref);
				}
				else //client not find on CHANNEL
				{
					//RPL ERR CLIENT NOT ON CHAN
					std::cout << "ERR CLIENT R NOT ON CHAN" << std::endl;
					std::string reply = "482 #" + target + " :Target are not not on channel";
					cli->send_to_client(reply);
				}
			}
			else if (mode.c_str()[1] == 'k')
			{
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
		}
		else
		{
			if (mode.c_str()[1] == 'i')
			{

			}
			else if (mode.c_str()[1] == 'o')
			{
				std::string      user;
				std::getline(args, user, ' ');
				Client *ref;

				ref = it->second->find_client(user);
				if (ref != NULL)
				{
					if (it->second->present_or_not_operators(ref))
						it->second->del_operator(ref);
					else
					{
						//RPL ERR CLIENT NOT ON CHAN
						std::cout << "ERR CLIENT R NOT ON CHAN" << std::endl;
						std::string reply = "482 #" + target + " :Target are not channel operator";
						cli->send_to_client(reply);
					}
				}
				else //client not find on CHANNEL
				{
					//RPL ERR CLIENT NOT ON CHAN
					std::cout << "ERR CLIENT R NOT ON CHAN" << std::endl;
					std::string reply = "482 #" + target + " :Target are not channel operator";
					cli->send_to_client(reply);
				}
			}
			else if (mode.c_str()[1] == 'k')
			{
				it->second->change_key("");
				it->second->change_secure(false);
				return ;
			}
		}
	}
	else // NEST PQS UN CHANNEL
		NULL;
}
//        target.erase(0,1);
		// std::string str = ":" + serv->get_hostname() + " 324 " + cli->get_nickname() + mode + " +i\r\n";
		// std::cout << str;
		// send(cli->get_fd(), str.c_str(), str.size(), 0);