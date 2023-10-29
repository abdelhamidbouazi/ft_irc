#ifndef TESTSERVER_HPP
#define TESTSERVER_HPP

#include "SimpleServer.hpp"

namespace HDE
{
    class TestServer : public SimpleServer
    {
        private:
            char buffer[30000];
            int new_socket;
            void accepter();
            void handler();
            void responder();
        public:
            TestServer();
            TestServer(int port);
            void launch();
    };
}


#endif // TESTSERVER_HPP
