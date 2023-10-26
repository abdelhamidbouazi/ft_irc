NAME = ircserv

CC = c++

Header = ./includes/Args.hpp \
		 ./includes/Client.hpp \
		 ./includes/Replies.hpp
# 		./includes/socket.hpp \
# 		./includes/connectingSocket.hpp \
# 		./includes/BindingSocket.hpp \
# 		./includes/ListeningSocket.hpp \
# 		./includes/TestServer.hpp \
# 		./includes/SimpleServer.hpp \
# 		./includes/Commande.hpp \


VERSION = -std=c++98 -Wall -Wextra -Werror
# VERSION = -std=c++98

SRC =	./srcs/Args.cpp \
		./srcs/Auth.cpp \
		./srcs/main2.cpp \
		./srcs/Client.cpp \
		./srcs/Replies.cpp \
		./srcs/Server.cpp \
		# ./srcs/main.cpp \
		# ./srcs/socket.cpp \
		# ./srcs/ConnectingSocket.cpp \
		# ./srcs/BindingSocket.cpp \
		# ./srcs/ListeningSocket.cpp \
		# ./srcs/TestServer.cpp \
		# ./srcs/SimpleServer.cpp \
		# ./srcs/Commande.cpp \


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
