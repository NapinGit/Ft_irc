#ifndef MACRO_HPP
#define MACRO_HPP

#define RPL_WELCOME(nick) "001 " + nick + " :Welcome " + nick + " to the ft_irc network"
#define ERR_PASSWDMISMATCH(nick)						"464 " + nick + " :Password incorrect"
#define ERR_NONICKNAMEGIVEN(nick)						"431 " + nick + " :Nickname not given"
#define ERR_UNKNOWNCOMMAND(nick, command)				"421 " + nick + " " + command + " :Unknown command"

#endif