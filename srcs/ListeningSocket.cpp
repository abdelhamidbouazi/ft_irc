#include "../includes/ListeningSocket.hpp"

HDE::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg, std::string password) : BindingSocket(domain, service, protocol, port, interface, password)
{
    this->backlog = bklg;
    // if (listen(this->get_sock(), this->backlog) < 0)
    // {
    //     std::cout << "Error listening to socket" << std::endl;
    //     exit(1);
    // }
    // std::cout << "Listening on port " << port << std::endl;
    start_listening();
    start_polling();

    // std::cout << "Listening socket 3" << std::endl;
    test_connection(listening);
}

void HDE::ListeningSocket::start_listening()
{
    // std::cout << "Listening socket 1" << std::endl;
    // std::cout << get_connection() << std::endl;
    listening = listen(get_sock(), backlog);
    // std::cout << get_sock() << std::endl;
    // std::cout << "Listening socket 2" << std::endl;
}

int HDE::ListeningSocket::get_listening()
{
    return listening;
}

int HDE::ListeningSocket::get_backlog()
{
    return backlog;
}