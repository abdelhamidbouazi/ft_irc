#include "../includes/BindingSocket.hpp"
#include "../includes/socket.hpp" 

int HDE::BindingSocket::connect_network(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address)); 
}

HDE::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface, std::string password) : HDE::SocketHde(domain, service, protocol, port, interface, password)
{
    set_connection(connect_network(get_sock(), get_address()));
    test_connection(get_connection());
}

HDE::BindingSocket::~BindingSocket()
{
}