#include "command.hpp"

void kill_cmd(Server *serv, Client *cli, std::string arg)
{
	if (cli->get_operator())
	{
		//shall get client
		std::map<int, Client *>::iterator it = serv->clients.begin();
		std::map<int, Client *>::iterator ite = serv->clients.end();
		std::string name = arg.substr(0 , arg.find(" "));
		while (it != ite)
		{
			if (it->second->get_nickname() == name)
			{
				serv->close_con(it->second);
				return;
			}
			it++;
		}
		//client not found;
	}
	else
	{
		std::string reply = ":Permission Denied- You're not an IRC operator" ;
		cli->send_to_client(reply);
		//not operator err no privilege
	}
}