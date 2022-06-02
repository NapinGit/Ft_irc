#include "Server.hpp"

Server::Server(const std::string &port, const std::string &password) : _alive(1), _ip("127.0.0.1"), _port(port), _password(password)
{
	socket_init();
}

Server::~Server()
{

}

void Server::start()
{
	pollfd polserv = {_sock, POLLIN, 0};
	mypoll.push_back(polserv);
	int i = 0;

	while (_alive)
	{
		if (poll(mypoll.begin().base(), mypoll.size() , -1) < 0)
			throw std::runtime_error("Poll: Error with poll and fd");
		std::vector<pollfd>::iterator it = mypoll.begin();
		std::vector<pollfd>::iterator ite = mypoll.end();
		while(it != ite)
		{
			/*if (mypoll.begin() == it)
			{
				std::cout << it->revents << " revent serv" << std::endl ;
				std::cout << it->events << " event serv" << std::endl ;
			}
			else
			{
				std::cout << it->revents << " revent client" << std::endl ;
				std::cout << it->events << " event client" << std::endl ;
			}*/
			// exit(0);
			if (it->revents == 0)
			{
				NULL;
			}
			if ((it->revents & POLLHUP) == POLLHUP)
			{
				std::cout << "Client asking for deconnexion" << std::endl ;
				exit(0);
				/*  deconnexion */
				break;
			}
			if ((it->revents & POLLIN) == POLLIN)
			{
				if (it->fd == _sock)
				{
					/* cree une nouvelle connexion */
					connecting_client();
					std::cout << "New client connected" << std::endl ;
					break;
				}
				/* analyse de l'entree*/
				read_msg(*it.base());
				//std::cout << "Message of client Read" << std::endl ;
				//write(socketDialogue, messageEnvoi, strlen(messageEnvoi)
			}

			
			it++;
		}
		
		/*if (i == 2)
			exit(0);
		i++;*/

	}
}

void Server::socket_init()
{
	_sock = socket(PF_INET, SOCK_STREAM, 0); //sock_stream = TCP ; PF_INET = ProtocolFamily
	if (_sock < 0)
    {
        throw std::runtime_error("Socket: Error while creating socket");
    }
		int val = 1;

	// Forcefully attaching socket to the port
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");
/*

	
	 * As requested from subject we set the socket to NON-BLOCKING mode
	 * allowing it to return any data that the system has in it's read buffer
	 * for that socket, but, it won't wait for that data.
	 */
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1) 
	{
		throw std::runtime_error("Error while setting socket to NON-BLOCKING.");
	}

	struct sockaddr_in pointDeRencontreLocal;
	bzero(&pointDeRencontreLocal, sizeof(pointDeRencontreLocal));
	pointDeRencontreLocal.sin_family = PF_INET;
	pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
	pointDeRencontreLocal.sin_port = htons(std::stoi(_port));
	if((bind(_sock, (struct sockaddr *)&pointDeRencontreLocal, sizeof(pointDeRencontreLocal))) < 0)
	{
		throw std::runtime_error("Socket: Error while binding socket");
	}

	if(listen(_sock, 5) < 0)
	{
		throw std::runtime_error("Listen: Error when listening on socket");
	}


}

void Server::connecting_client()
{
	pollfd polclient = {0 , POLLIN, 0};
	struct sockaddr_in client_addr;
	socklen_t sizeClient_addr = sizeof(client_addr);
	polclient.fd = accept(_sock, (sockaddr *)&client_addr, &sizeClient_addr);
	if (polclient.fd < 0)
	{
		throw std::runtime_error("Accept : Error when connecting a new client");
	}
	mypoll.push_back(polclient);
	
	//class client to create and to insert into a client map of Server class

}

void Server::read_msg(pollfd &client)
{
	char buffer[6];
	bzero(&buffer, sizeof(buffer));
	if (recv(client.fd, buffer, 5, 0) < 0)
		throw std::runtime_error("Error while reading buffer from client.");

	std::cout << buffer ;
	/*if ((client.revents & POLLIN) == POLLIN)
		std::cout << std::endl;*/
}
