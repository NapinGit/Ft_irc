NAME1	=	ircserv
CC = clang++
OBJ_DIR = obj/
#OBJ_DIR_D = obj/Command
OBJ_DIR_E = obj/srcs/Command
INCLUDE =  include/Server.hpp include/Channel.hpp include/Client.hpp include/macro.hpp
#-Werror -Wextra -Wall -std=c++98
FLAGS	= -g -Werror -Wextra -Wall -std=c++98
OBJ	= srcs/main.cpp srcs/Server.cpp srcs/Client.cpp srcs/Channel.cpp srcs/Command/invite.cpp srcs/Command/join.cpp srcs/Command/kick.cpp srcs/Command/kill.cpp srcs/Command/mode.cpp srcs/Command/nick.cpp srcs/Command/part.cpp srcs/Command/pass.cpp srcs/Command/pong.cpp srcs/Command/privmsg.cpp srcs/Command/quit.cpp srcs/Command/user.cpp srcs/Command/cap.cpp srcs/Command/notice.cpp srcs/Command/who.cpp
SUPP_DIR = rm -rf $(OBJ_DIR)
SUPP_NAME = rm -f $(NAME1)
DEBUG = valgrind

OBJ_PREFIX =	$(addprefix $(OBJ_DIR),$(OBJ:%.cpp=%.o))

all :	$(NAME1)

$(NAME1) : $(INCLUDE) $(OBJ_PREFIX)
	$(CC) -I/include $(FLAGS) $(OBJ_PREFIX) -o $(NAME1)

$(OBJ_DIR)%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
#	@mkdir -p $(OBJ_DIR_D)
	@mkdir -p $(OBJ_DIR_E)
	$(CC) $(FLAGS) -c $< -o $@

val : $(NAME1)
	@echo "IRC server started on 5000 with pass yolo"
	$(DEBUG) ./ircserv 5000 yolo

clean :
	$(SUPP_DIR)

fclean : clean
	$(SUPP_NAME)

re : fclean all