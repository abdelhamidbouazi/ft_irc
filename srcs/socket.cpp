#include "../includes/socket.hpp"
#include "../includes/Commande.hpp"
#include <string.h>
#include <stdio.h>

HDE::SocketHde::SocketHde(int domain, int service, int protocol, int port, unsigned long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);
	sock = socket(domain, service, protocol);
	test_connection(sock);

	// connection = connect_network(sock, address);
	// test_connection(connection);

	// adding this to allow socket discrptor to be reused
	on = 1;
	rc = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	test_connection_for_setsockopt(rc);
	//using non blocking socket
	if(fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
	{
		perror("Failled to set socket to non blocking...");
		close(sock);
		exit(EXIT_FAILURE);
	}

}

void HDE::SocketHde::start_polling()
{
	memset (fds, 0 , sizeof(fds));
	fds[0].fd = sock;
	fds[0].events = POLLIN | POLLOUT;
	fds[0].revents = 0;
	timeout = (3 * 60 * 1000);
	end_server = false;
	nfds = 1;
	int current_size = 0;
	int close_conn, len;
	char buffer[800];
	int compress_array = false;
	int new_sd = -1;

	while(!end_server)
	{
		rc = poll(fds, nfds, -1);

		if(rc < 0)
		{
			perror("  poll() failed");
			close(sock);
			break;
		}
		if(fds[0].revents & POLLIN)
		{
			std::cout << " Listening socket is readable" << std::endl;

			connection = accept(sock, NULL, NULL);
			if(connection < 0)
			{
				if(errno != EWOULDBLOCK)
				{
					perror("  accept() failed");
					end_server = true;
				}
				break;
			}
			else
			{
				std::cout << " New incoming connection - " << connection << std::endl;
				fds[nfds].fd = connection;
				fds[nfds].events = POLLIN;
				nfds++;
			}
		}
		else
		{
			current_size = nfds;
			Commande obj;
			for(int i = 0; i < current_size; i++)
			{
				if(fds[i].revents & POLLIN )
				{
					memset(buffer, 0, sizeof(buffer));
					rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if(rc == -1)
					{
						if(errno != EWOULDBLOCK)
						{
							perror("  recv() failed");
							close_conn = true;
							close(fds[i].fd);
						}
						break;
					}
					if(rc == 0)
					{
						std::cout << "  Connection closed" << std::endl;
						close_conn = true;
						close(fds[i].fd);
						break;
					}
					else
					{
						std::cout << "receiv data ==== " << buffer;
						std::string msg(buffer);
						obj.start_parssing(msg,i);
					}
					
				}
			}
		}

		
	}
}


void HDE::SocketHde::test_connection(int item_to_test)
{
	if(item_to_test < 0)
	{
		perror("Failed to connect...");
		exit(EXIT_FAILURE);
	}
}

void HDE::SocketHde::test_connection_for_setsockopt(int item_to_test)
{
	if(item_to_test < 0)
	{
		perror("Failled to set socket option...");
		close(sock);
		exit(EXIT_FAILURE);
	}
}

std::string HDE::SocketHde::getHostAdresse(){
	std::system( "ifconfig | grep 'inet ' | awk 'NR==2 {print $2}' > .log" );
	std::stringstream ss;
	ss << std::ifstream( ".log" ).rdbuf();
	std::system( "rm -f .log" );
	return (ss.str().substr( 0, ss.str().find( '\n' ) ));
}


std::string HDE::SocketHde::ClientIp(int socket) {
	char buffer[INET_ADDRSTRLEN];
	struct sockaddr_in clientAddress;
	socklen_t addrLen = sizeof(clientAddress);

	if (socket >= 0 && getpeername(socket, (struct sockaddr*)&clientAddress, &addrLen) == 0) {
		if (inet_ntop(AF_INET, &clientAddress.sin_addr, buffer, INET_ADDRSTRLEN)) {
			this->localhost = buffer;
			if (this->localhost == "127.0.0.1")
				this->localhost = getHostAdresse();
			return localhost;
		}
		else {
			perror("inet_ntop() failed");
			return NULL;
		}
	}
	else {
		perror("getpeername() failed");
		return NULL;
	}
	return NULL;
}


struct sockaddr_in HDE::SocketHde::get_address()
{
	return address;
}

int HDE::SocketHde::get_sock()
{
	return sock;
}

int HDE::SocketHde::get_connection()
{
	return connection;
}

void HDE::SocketHde::set_connection(int connection)
{
	this->connection = connection;
}