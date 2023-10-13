#include "../includes/socket.hpp"

HDE::SocketHde(int domain, int sevice, int protocol, int port, unsigned long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);

	sock = socket(domain, service, protocol, port);
	test_connection(sock);

	connection = connect_network(sock, address);
	test_connection(connection);
}

HDE::SocketHde::test_connection(int item_to_test)
{
	if(item_to_test < 0)
	{
		perror("Failled to connect...");
		exit(EXIT_FAILURE);
	}
}

struct sockaddr_in HDE::SocketHde::get_address()
{
	return address;
}

nt sockaddr_in HDE::SocketHde::get_connection()
{
	return connection;
}
