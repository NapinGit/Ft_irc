#include "../../include/command.hpp"

void mode_cmd(Server *serv, Client *cli, std::string arg)
{
	std::istringstream      					args;
	std::string             					mode;
	std::string             					target;
	std::string             					msg;
	std::map<std::string, Channel *>::iterator  it;

	args.str(arg);
	std::getline(args, target, ' ');
	std::getline(args, mode, ' ');
	if (target.c_str()[0] == '#')
	{
		target.erase(0, 1);
		it = (serv->_channels).find(target);
		if (mode.length() == 0)
			return;
		if (it == serv->_channels.end())
		{
			std::string reply = "403 #" + target + " :#" + target;
			cli->send_to_client(reply);
			return;
		}
		if (!it->second->present_or_not(cli))
		{
			std::string reply = "442 #" + target + " :You're not on channel";
			cli->send_to_client(reply);
			return;
		}
		if (!it->second->present_or_not_operators(cli))
		{
			std::string reply = "482 #" + target + " :You're not channel operator";
			cli->send_to_client(reply);
			return;
		}
		if (mode.c_str()[0] == '+')
		{
			if (mode.c_str()[1] == 'o')
			{
				std::string      	user;
				Client 				*ref;

				std::getline(args, user, ' ');
				ref = it->second->find_client(user);
				if (ref != NULL)
					it->second->add_operator(ref);
				else
				{
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
				return ;
			}
		}
		else
		{
			if (mode.c_str()[1] == 'o')
			{
				std::string      user;
				Client *ref;

				std::getline(args, user, ' ');
				ref = it->second->find_client(user);
				if (ref != NULL)
				{
					if (it->second->present_or_not_operators(ref))
						it->second->del_operator(ref);
					else
					{
						std::cout << "ERR CLIENT R NOT ON CHAN" << std::endl;
						std::string reply = "482 #" + target + " :Target are not channel operator";
						cli->send_to_client(reply);
					}
				}
				else
				{
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
	else
		NULL;
}