#ifndef LISTENING_SOCKET_HPP
#define LISTENING_SOCKET_HPP


#include "BindingSocket.hpp"
#include "socket.hpp"

namespace HDE 
{
    class ListeningSocket : public BindingSocket
    {
        private:
            int backlog;
            int listening;
        public:
            ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg, std::string password);
            void start_listening();
            int get_listening();
            int get_backlog();
            // ~ListeningSocket();
    };
 } 


#endif 
