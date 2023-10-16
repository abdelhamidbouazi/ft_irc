#ifndef BINDINGSOCKET_HPP
#define BINDINGSOCKET_HPP



#include "../includes/socket.hpp"

namespace HDE 
{
    class BindingSocket
    {
        private:
        
        public:
            BindingSocket(int domain, int service, int protocol, int port, u_long interface);
            int connect_to_network(int sock, struct sockaddr_in address);
            ~BindingSocket();
    };
}

#endif