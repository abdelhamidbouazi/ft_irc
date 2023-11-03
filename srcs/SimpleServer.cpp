#include "../includes/SimpleServer.hpp"


HDE::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg, std::string password)
{
    this->socket = new ListeningSocket(domain, service, protocol, port, interface, bklg, password);
}

HDE::ListeningSocket *HDE::SimpleServer::get_socket()
{
    return this->socket;
}