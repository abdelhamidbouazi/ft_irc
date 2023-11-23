NAME = ircserv

CC = c++

Header =	./includes/socket.hpp \
			./includes/Commande.hpp \
			./includes/Client.hpp \
			./includes/Args.hpp \
			./includes/Replies.hpp \
			./includes/Channel.hpp \

# VERSION = -std=c++98 -Wall -Wextra -Werror  -fsanitize=address
VERSION = -std=c++98 -Wall -Wextra -Werror

SRC =	./srcs/main.cpp \
		./srcs/socket.cpp \
		./srcs/Commande.cpp \
		./srcs/Client.cpp \
		./srcs/Args.cpp \
		./srcs/Auth.cpp \
		./srcs/Replies.cpp \
		./srcs/Channel.cpp \
		./srcs/Check.cpp \
		./srcs/SendMessage.cpp \
		./srcs/Commands/Mode.cpp \
		./srcs/Commands/Join.cpp \
		./srcs/Commands/Part.cpp \
		./srcs/Commands/Topic.cpp \
		./srcs/Commands/Privmsg.cpp \
		./srcs/Commands/Bot.cpp \
		./srcs/Commands/Invite.cpp \
		./srcs/Commands/Kick.cpp \
		./srcs/Commands/User.cpp \
		./srcs/Commands/Nick.cpp \
		./srcs/Commands/Pass.cpp \
		./srcs/Commands/Quit.cpp

OBJECTS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(VERSION) $(OBJECTS) -o $(NAME)

%.o : %.cpp $(Header)
	$(CC) $(VERSION) -o $@ -c $<

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
