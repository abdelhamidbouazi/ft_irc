#include "../includes/ListeningSocket.hpp"

HDE::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg, std::string password) : BindingSocket(domain, service, protocol, port, interface, password)
{
    this->backlog = bklg;
    start_listening();
    start_polling();
    test_connection(listening);
}

void HDE::ListeningSocket::start_listening()
{
    listening = listen(get_sock(), backlog);
}

int HDE::ListeningSocket::get_listening()
{
    return listening;
}

int HDE::ListeningSocket::get_backlog()
{
    return backlog;
}