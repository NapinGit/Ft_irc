#ifndef SERVER_HPP
# define SERVER_HPP
#include <errno.h>  
# include <iostream>
# include <sys/socket.h>
# include <sys/types.h> 
# include <stdlib.h> /* pour exit */
# include <string.h> /* pour memset */
# include <netinet/in.h> /* pour struct sockaddr_in */
# include <arpa/inet.h> /* pour htons et inet_aton */
# include <unistd.h> /* pour sleep */
# include <poll.h>
# include <vector>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h> 
# include <map>
# include <netdb.h>
# include <istream>
# include <sstream>
# include <cstring>
# include "Client.hpp"
# include "Channel.hpp"
# include "macro.hpp"
# include "command.hpp"

# define MAX_CON 100

class Server
{
	private:
		 bool _alive;
		 int _sock;

		 const std::string 																_hostname;
		 std::string 																	_inhostname;
		 const std::string 																_port;
		 const std::string 																_password;
		 std::vector<pollfd>															mypoll;
		void socket_init();

    public:
		std::map<int , Client *> 														clients;
		std::map <std::string, void (*)(Server *serv, Client *cli, std::string arg)> 	cmd;
		std::map<std::string, Channel *>												_channels;


	Server(const std::string &port, const std::string &password);
	~Server();

	void 			start();
	void 			connecting_client();
	void 			read_msg(pollfd &client);
	void 			close_con(std::vector<pollfd>::iterator it);
	void 			close_con(Client *cli);
	void 			signal_handler(int signal);
	void 			cmd_handler(char *buff, Client *cli);
	void 			get_client_info(pollfd &client);
	void 			init_cmd();
	

	/*

		Accessor
	
	*/
	std::string 	get_password() const;
	std::string 	get_hostname() const;
	std::string 	get_inhostname() const;
};
#endif