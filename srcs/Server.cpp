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
	pollfd mypoll = {_sock, POLLIN, 0};

	while (_alive)
	{
		if (poll(mypoll, 1 , -1) < 0)
			throw std::runtime_error("Poll: Error with poll and fd");
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
	/*if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");


	/*
	 * As requested from subject we set the socket to NON-BLOCKING mode
	 * allowing it to return any data that the system has in it's read buffer
	 * for that socket, but, it won't wait for that data.
	 
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
		throw std::runtime_error("Error while setting socket to NON-BLOCKING.");
	}*/

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
