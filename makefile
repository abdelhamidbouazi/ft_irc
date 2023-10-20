NAME = ircserv

CC = c++

Header =	./includes/socket.hpp \
		./includes/connectingSocket.hpp \
		./includes/BindingSocket.hpp \
		./includes/ListeningSocket.hpp \
		./includes/TestServer.hpp \
		./includes/SimpleServer.hpp \
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
		# ./src/hdelibc-socket.cpp \
		# ./src/hdelibc-networking.cpp \

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
