NAME1	=	ircserv
CC = clang++
OBJ_DIR = obj/
OBJ_DIR_D = obj/Command
#-Werror -Wextra -Wall -std=c++98
FLAGS	= -g -Werror -Wextra -Wall -std=c++98
OBJ	=  main.cpp Server.cpp Client.cpp Channel.cpp Command/invite.cpp Command/join.cpp Command/kick.cpp Command/kill.cpp Command/mode.cpp Command/nick.cpp Command/part.cpp Command/pass.cpp Command/pong.cpp Command/privmsg.cpp Command/quit.cpp Command/user.cpp Command/utils.cpp Command/cap.cpp
SUPP_DIR = rm -rf $(OBJ_DIR)
SUPP_NAME = rm -f $(NAME1)
DEBUG = valgrind

OBJ_PREFIX =	$(addprefix $(OBJ_DIR),$(OBJ:%.cpp=%.o))

all :	$(NAME1)

$(NAME1) : $(INCLUDE) $(OBJ_PREFIX)
	$(CC) $(FLAGS) $(OBJ_PREFIX) -o $(NAME1)

$(OBJ_DIR)%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR_D)
	$(CC) $(FLAGS) -c $< -o $@

val : $(NAME1)
	@echo "IRC server started on 5000 with pass yolo"
	$(DEBUG) ./ircserv 5000 yolo

clean :
	$(SUPP_DIR)

fclean : clean
	$(SUPP_NAME)

re : fclean all