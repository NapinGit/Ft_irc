#ifndef COMMAND_HPP
#define COMMAND_HPP

class Server;
class Client;
#include "../Server.hpp"
#include "../Client.hpp"
#include "../Channel.hpp"

/*

    COMMANDE RELATIVE A L'AUTHENTIFICATION

*/

 void cap_cmd(Server *serv, Client *cli, std::string arg);
 void pass_cmd(Server *serv, Client *cli, std::string arg);
 void nick_cmd(Server *serv, Client *cli, std::string arg);

/*

    COMMANDE RELATIVE AUX OPERATEURS

*/

void kill_cmd(Server *serv, Client *cli, std::string arg);


/*

    COMMANDE RELATIVE AUX OPERATEURS DE CANAUX

*/

// void invite_cmd(Server *serv, Client *cli, std::string arg);
void mode_cmd(Server *serv, Client *cli, std::string arg);
// void kick_cmd(Server *serv, Client *cli, std::string arg);
// void topic_cmd(Server *serv, Client *cli, std::string arg);

/*

    COMMANDE RELATIVE AUX UTILISATEURS

*/

void join_cmd(Server *serv, Client *cli, std::string arg);
void privmsg_cmd(Server *serv, Client *cli, std::string arg);
 void user_cmd(Server *serv, Client *cli, std::string arg);
void pong_cmd(Server *serv, Client *cli, std::string arg);
void quit_cmd(Server *serv, Client *cli, std::string arg);


#endif