#ifndef SIMPLESERVER_HPP
#define SIMPLESERVER_HPP


#include "../includes/ListeningSocket.hpp"
#include "../includes/BindingSocket.hpp"
#include "../includes/socket.hpp"
#include "../includes/ConnectingSocket.hpp"


namespace HDE
{
    class SimpleServer
    {
        private:
            ListeningSocket *socket;
            virtual void accepter() = 0;
            virtual void handler() = 0;
            virtual void responder() = 0;

        public:
            SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg, std::string password);     
            virtual void launch() = 0;
            ListeningSocket *get_socket();
    };
}


#endif
