#include "../includes/BindingSocket.hpp"
#include "../includes/socket.hpp" 

int HDE::BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address)); 
}

HDE::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) : HDE::SocketHde(domain, service, protocol, port, interface)
{
    set_connection(connect_to_network(get_sock(), get_address()));
    test_connection(get_connection());
    // connection = connect_to_network(get_sock(), get_address());
    // test_connection(connection);
}

HDE::BindingSocket::~BindingSocket()
{
    // close(get_sock());
}