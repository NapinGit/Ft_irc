#ifndef MACRO_HPP
#define MACRO_HPP

#define RPL_WELCOME(nick) "001 " + nick + " :Welcome " + nick + " to the ft_irc network"
#define ERR_NOSUCHNICK(source)					"401 " + source + " :No such nickname"

#define ERR_PASSWDMISMATCH(nick)						"464 " + nick + " :Password incorrect"
#define ERR_NONICKNAMEGIVEN(nick)						"431 " + nick + " :Nickname not given"
#define ERR_UNKNOWNCOMMAND(nick, command)				"421 " + nick + " " + command + " :Unknown command"
#define ERR_NICKNAMEINUSE(source, nick)					"422 " + source + " " + nick  + " :Nickname is already in use"
#define ERR_ALREADYREGISTERED(source)					"462 " + source + " :You may not reregister"
#endif