# include "../includes/ListeningSocket.hpp"
# include "../includes/BindingSocket.hpp"
#include "../includes/socket.hpp"
#include "../includes/ConnectingSocket.hpp"
#include "../includes/SimpleServer.hpp"
#include "../includes/TestServer.hpp"
#include <iostream>

using namespace HDE;

int main ()
{
    // std::cout << "Starting server..." << std::endl;
    // // HDE::SocketHde *socket = new HDE::SocketHde(AF_INET, SOCK_STREAM, 0, 5050, INADDR_ANY);
    // std::cout << "binding socket..." << std::endl;
    // HDE::BindingSocket bs = HDE::BindingSocket(AF_INET, SOCK_STREAM, 0, 81, INADDR_ANY);
    // std::cout << "Listening socket..." << std::endl;
    // HDE::ListeningSocket ls = HDE::ListeningSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    // std::cout << "success!" << std::endl;
    HDE::TestServer ts;
}
