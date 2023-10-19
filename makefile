NAME = ircserv

CC = c++

Header =	./includes/socket.hpp \
		./includes/connectingSocket.hpp \
		./includes/BindingSocket.hpp \
		./includes/ListeningSocket.hpp
		# ./includes/hdelibc-socket.hpp \
		# ./includes/hdelibc-networking.hpp \

VERSION = -std=c++98 -Wall -Wextra -Werror

SRC =	./srcs/main.cpp \
		./srcs/socket.cpp \
		./srcs/ConnectingSocket.cpp \
		./srcs/BindingSocket.cpp \
		./srcs/ListeningSocket.cpp
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
