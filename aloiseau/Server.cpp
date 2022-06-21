#include "Server.hpp"
// #include <sys/types.h>
// #include <ifaddrs.h>
// #define INTERFACE "wl"

Server::Server(const std::string &port,const std::string &password) : _alive(1), _hostname("127.0.0.1"), _port(port), _password(password)
{
	socket_init();
	init_cmd();
	// std::map<std::string, void (*)(Server *, Client *, std::string arg) >::iterator it = cmd.begin();
}

Server::~Server()
{
	mypoll.clear();
	std::map<int, Client *>::iterator it = clients.begin();
	std::map<int, Client *>::iterator ite = clients.end();
	while (it != ite)
	{
		delete it->second;
		it++;
	}
	clients.clear();

	std::map<std::string, Channel *>::iterator itc = _channels.begin();
	std::map<std::string, Channel *>::iterator itce = _channels.end();
	while (itc != itce)
	{
		delete itc->second;
		itc++;
	}
	_channels.clear();
}

void Server::init_cmd()
{
	cmd.insert(std::make_pair("PASS", &pass_cmd));
	cmd.insert(std::make_pair("NICK", &nick_cmd));
	cmd.insert(std::make_pair("USER", &user_cmd));
	cmd.insert(std::make_pair("kill", &kill_cmd));
	cmd.insert(std::make_pair("JOIN", &join_cmd));
	cmd.insert(std::make_pair("PING", &pong_cmd));
	cmd.insert(std::make_pair("PRIVMSG", &privmsg_cmd));
	cmd.insert(std::make_pair("MODE", &mode_cmd));
	cmd.insert(std::make_pair("CAP", &cap_cmd));
	cmd.insert(std::make_pair("QUIT", &quit_cmd));
	cmd.insert(std::make_pair("KICK", &kick_cmd));
	cmd.insert(std::make_pair("PART", &part_cmd));
	cmd.insert(std::make_pair("INVITE", &invite_cmd));
}

void Server::start()
{
	pollfd polserv = {_sock, POLLIN, 0};
	mypoll.push_back(polserv);
	// int i = 0;
	std::vector<pollfd>::iterator it;
	std::vector<pollfd>::iterator ite;

	ite = mypoll.end();
	while (_alive)
	{
		// std::cout << "poll begin" << std::endl;
		if (poll(mypoll.begin().base(), mypoll.size() , -1) < 0)
			throw std::runtime_error("Poll: Error with poll and fd");
		// std::cout << "poll end" << std::endl;
		it = mypoll.begin();
		ite = mypoll.end();
		while(it != ite)
		{
			if (it->revents == 0)
			{
				NULL;
			}
			else if ((it->revents & POLLHUP) == POLLHUP)
			{
				close_con(it);
				//deco(it);
				/*  deconnexion */
				break;
			}
			else if ((it->revents & POLLIN) == POLLIN)
			{
				if (it->fd == _sock)
				{
					/* cree une nouvelle connexion */
					connecting_client();
					std::cout << "New client connected" << std::endl;
					break;
				}
				/* analyse de l'entree*/
				read_msg(*it.base());
			}
			it++;
		}
	}
}

/*std::string Server::get_interface_ip()
{
    struct ifaddrs* 	addrs = NULL;
    struct ifaddrs* 	ptr_entry;
	std::string 		interface_name;
	char 				buffer[INET_ADDRSTRLEN];
    
	if(getifaddrs(&addrs) != 0)
	{
        std::cout << "ERROR getifaddrs()" << std::endl;
        return NULL;
    }
	ptr_entry  = addrs;
	while(ptr_entry != NULL)
	{
		bzero(&buffer, INET_ADDRSTRLEN);
		interface_name = std::string(ptr_entry->ifa_name);
		if (!interface_name.find(INTERFACE)) 												// INTERFACE FOUND ?
			if( ptr_entry->ifa_addr != NULL && ptr_entry->ifa_addr->sa_family == AF_INET) 	//address non null && IPV4 ?
			{
				inet_ntop(ptr_entry->ifa_addr->sa_family,&((struct sockaddr_in*)(ptr_entry->ifa_addr))->sin_addr,buffer,INET_ADDRSTRLEN);
				break;
			}
		ptr_entry = ptr_entry->ifa_next;
	}
	return (std::string(buffer));
}*/

void Server::socket_init()
{
	int 				val = 1;
	struct sockaddr_in 	pointDeRencontreLocal;

	_sock = socket(PF_INET, SOCK_STREAM, 0); //sock_stream = TCP ; PF_INET = ProtocolFamily
	bzero(&pointDeRencontreLocal, sizeof(pointDeRencontreLocal));
	pointDeRencontreLocal.sin_family = PF_INET;
	pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
	pointDeRencontreLocal.sin_port = htons( std::atoi( _port.c_str() ));

	if (_sock < 0)
        throw std::runtime_error("Socket: Error while creating socket");
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1) 
		throw std::runtime_error("Error while setting socket to NON-BLOCKING.");
	if((bind(_sock, (struct sockaddr *)&pointDeRencontreLocal, sizeof(pointDeRencontreLocal))) < 0)
		throw std::runtime_error("Socket: Error while binding socket");
	if(listen(_sock, MAX_CON) < 0)
		throw std::runtime_error("Listen: Error when listening on socket");
}

void Server::get_client_info(pollfd &client)
{
	char buffer[100];
	if (recv(client.fd, buffer, 99, 0) < 0)
		throw std::runtime_error("Error while reading buffer from client.");
}

void Server::connecting_client()
{
	pollfd 				polclient = {0 , POLLIN, 0};
	struct sockaddr_in 	client_addr;
	socklen_t 			sizeClient_addr = sizeof(client_addr);
	char 				host[NI_MAXHOST];

	polclient.fd = accept(_sock, (sockaddr *)&client_addr, &sizeClient_addr);
	if (polclient.fd < 0)
	{
		throw std::runtime_error("Accept : Error when connecting a new client");
	}
	mypoll.push_back(polclient);
	if (getnameinfo((struct sockaddr *)&client_addr, sizeof(client_addr), host, NI_MAXHOST,NULL, 0 , NI_NUMERICHOST | NI_NUMERICSERV ) != 0)
		throw std::runtime_error("Error while getting hostname on new client.");
	Client *new_client = new Client(polclient.fd);
	std::string str = host;
	new_client->change_hostname(str);
	clients.insert(std::make_pair(new_client->get_fd(), new_client));

	//class client to create and to insert into a client map of Server class
	read_msg(polclient);
}

void Server::read_msg(pollfd &client)
{
	char buffer[1000];
	std::string st;
	std::map<int, Client *>::iterator it;

	bzero(&buffer, sizeof(buffer));
	if (recv(client.fd, buffer, 999, 0) < 0)
		throw std::runtime_error("Error while reading buffer from client.");
	st = buffer;
	std::cout << buffer;
	it = clients.find(client.fd);
	cmd_handler(buffer, it->second);
}

void Server::cmd_handler(char *buff, Client *cli)
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
        std::getline(l, arg);
		if (arg[arg.size() - 1] == '\r')
			arg.erase((arg.size() - 1), 1);
        it = cmd.find(cmdd);
		if (it == cmd.end())
		{
			std::string reply = ERR_UNKNOWNCOMMAND(cli->get_nickname(), cmdd);
        	cli->send_to_client(reply);
		}	
		else
			(it->second)(this, cli, arg);
        l.clear();
    }
}

void Server::close_con(std::vector<pollfd>::iterator it)
{
	std::map<int , Client *>::iterator itc = clients.find(it->fd);
	std::map<std::string , Channel *>::iterator itchan;
	std::map<std::string , Channel *>::iterator itchane;

	for (itchan = (itc->second)->_channels.begin(), itchane = (itc->second)->_channels.end(); itchan != itchane; itchan++)
	{
		if (itchan->second->present_or_not_operators(itc->second))
			itchan->second->del_operator(itc->second);
		itchan->second->del(itc->second);
	}
	// itc->second->add_channel

	close(it->fd);
	mypoll.erase(it);
	//virer le client de la liste et delete la value de la map (it->second)
}

void Server::close_con(Client *cli)                                                                                           
{
	std::map<std::string , Channel *>::iterator itchan;
	std::map<std::string , Channel *>::iterator itchane;
	std::vector<pollfd>::iterator itpoll;
	std::vector<pollfd>::iterator itpolle;

	for (itchan = cli->_channels.begin(), itchane = cli->_channels.end(); itchan != itchane; itchan++)
	{
		itchan->second->del(cli);
		itchan->second->leave_msg(itchan->second, cli, "");
		if (itchan->second->nb_clients() == 0)
		{
			delete (itchan->second);
			_channels.erase(itchan->first);
		}	

	}
	// itc->second->add_channel
	close(cli->get_fd());

	itpoll = mypoll.begin();
	itpolle = mypoll.end();

	while (itpoll->fd != cli->get_fd() && itpoll != itpolle)
		itpoll++;
	if (itpoll != itpolle)
	{
		mypoll.erase(itpoll);
		clients.erase(clients.find(cli->get_fd()));
		delete(cli);
	}
	
}

std::string Server::get_password() const
{
	return (_password);
}

std::string Server::get_hostname() const
{
	return (_hostname);
}

std::string Server::get_inhostname() const
{
	return (_inhostname);
}
