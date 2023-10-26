NAME = ircserv

CC = c++

<<<<<<< HEAD
Header =  includes/Args.hpp includes/Client.hpp includes/Replies.hpp

VERSION = -std=c++98  -Wall -Wextra -Werror

SRC =	srcs/main2.cpp srcs/Args.cpp srcs/Server.cpp srcs/Client.cpp srcs/Auth.cpp \
			srcs/Replies.cpp
=======
Header =	./includes/socket.hpp \
		./includes/connectingSocket.hpp \
		./includes/BindingSocket.hpp \
		./includes/ListeningSocket.hpp \
		./includes/TestServer.hpp \
		./includes/SimpleServer.hpp \
		./includes/Commande.hpp \
		# ./includes/hdelibc-socket.hpp \
		# ./includes/hdelibc-networking.hpp \

VERSION = -std=c++98 -Wall -Wextra -Werror
# VERSION = -std=c++98 

SRC =	./srcs/main.cpp \
		./srcs/socket.cpp \
		./srcs/ConnectingSocket.cpp \
		./srcs/BindingSocket.cpp \
		./srcs/ListeningSocket.cpp \
		./srcs/TestServer.cpp \
		./srcs/SimpleServer.cpp \
		./srcs/Commande.cpp \
		# ./src/hdelibc-socket.cpp \
		# ./src/hdelibc-networking.cpp \
>>>>>>> 95cc382a4f98bfe5f2635eca99a1b30a3a4cbd5d

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
