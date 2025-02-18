SRCS			= \
srcs/main.cpp	\
srcs/Classes/Server.cpp	\
srcs/Classes/Client.cpp	\
srcs/Classes/ClientChannel.cpp	\
srcs/Classes/Channel.cpp	\
srcs/Classes/ParsingInput.cpp	\
srcs/Commands/pass.cpp	\
srcs/Commands/nick.cpp	\
srcs/Commands/user.cpp	\
srcs/Commands/quit.cpp	\
srcs/Commands/join.cpp	\
srcs/Commands/mode.cpp	\
srcs/Commands/topic.cpp	\
srcs/Commands/names.cpp	\
srcs/Commands/part.cpp	\
srcs/Commands/invite.cpp	\
srcs/Commands/kick.cpp	\
srcs/Commands/privmsg.cpp	\
srcs/Commands/oper.cpp	\
srcs/Commands/bot.cpp	\

OBJS			= $(SRCS:.cpp=.o)

DEPS			= $(SRCS:.cpp=.d)

CC				= c++

FLAGS			= -MD -Wall -Wextra -Werror -std=c++98 -I includes/

RM				= rm -f

NAME			= ircserv


all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)

.cpp.o		:
				${CC} ${FLAGS} -c $< -o ${<:.cpp=.o}

clean:
				$(RM) $(OBJS)
				$(RM) $(DEPS)

fclean:			clean
				$(RM) $(NAME)

-include $(DEPS)

re:				fclean $(NAME)

.PHONY:			all clean fclean re