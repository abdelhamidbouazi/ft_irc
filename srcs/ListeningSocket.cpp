#include "../includes/ListeningSocket.hpp"

HDE::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg) : BindingSocket(domain, service, protocol, port, interface)
{
    this->backlog = bklg;
    // if (listen(this->get_sock(), this->backlog) < 0)
    // {
    //     std::cout << "Error listening to socket" << std::endl;
    //     exit(1);
    // }
    // std::cout << "Listening on port " << port << std::endl;
    start_listening();
    test_connection(listening);
}

void HDE::ListeningSocket::start_listening()
{
    listening = listen(get_connection(), backlog);
}