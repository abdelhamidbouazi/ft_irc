NAME = ircserv

CC = c++

Header =	./includes/socket.hpp \
			./includes/connectingSocket.hpp \
			./includes/BindingSocket.hpp \
			./includes/ListeningSocket.hpp \
			./includes/TestServer.hpp \
			./includes/SimpleServer.hpp \
			./includes/Commande.hpp \
			./includes/Client.hpp \
			./includes/Args.hpp \
			./includes/Replies.hpp \
			./includes/Channel.hpp \

VERSION = -std=c++98 -Wall -Wextra -Werror  -fsanitize=address

SRC =	./srcs/main.cpp \
		./srcs/socket.cpp \
		./srcs/ConnectingSocket.cpp \
		./srcs/BindingSocket.cpp \
		./srcs/ListeningSocket.cpp \
		./srcs/TestServer.cpp \
		./srcs/SimpleServer.cpp \
		./srcs/Commande.cpp \
		./srcs/Client.cpp \
		./srcs/Args.cpp \
		./srcs/Auth.cpp \
		./srcs/Replies.cpp \
		./srcs/Channel.cpp \
		./srcs/Check.cpp \
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
