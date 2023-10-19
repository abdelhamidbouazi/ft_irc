#ifndef BINDINGSOCKET_HPP
#define BINDINGSOCKET_HPP



#include "socket.hpp"

namespace HDE 
{
    class BindingSocket: public SocketHde
    {
        public:
            BindingSocket(int domain, int service, int protocol, int port, u_long interface);
            int connect_network(int sock, struct sockaddr_in address);
            ~BindingSocket();
    };
}

#endif