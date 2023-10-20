NAME = ircserv

CC = c++

Header =  includes/Args.hpp

VERSION = -std=c++98  -Wall -Wextra -Werror

SRC =	srcs/main.cpp srcs/Args.cpp

OBJECTS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(VERSION) $(OBJECTS) -o $(NAME)

%.opp : %.cpp $(Header)
	$(CC) $(VERSION)  -o $@ -c $<

clean:
	rm -rf $(OBJECTS)
fclean: clean
	rm -rf $(NAME)

re: fclean all
