#ifndef CONNECTING_SOCKET_HPP
# define CONNECTING_SOCKET_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>

#include "../includes/socket.hpp"
#include "BindingSocket.hpp"


namespace HDE {

    class ConnectingSocket {
        public:
            ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);
            int connect_to_network(int sock, struct sockaddr_in address);
    };
}

#endif
