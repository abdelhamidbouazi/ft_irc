#include "../includes/socket.hpp"
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
	start_polling();
}

void HDE::SocketHde::start_polling()
{
	memset (fds, 0 , sizeof(fds));
	fds[0].fd = sock;
	fds[0].events = POLLIN;
	timeout = (3 * 60 * 1000);
	end_server = false;
	nfds = 1;
	int current_size = 0;

	while(end_server == false)
	{
		std::cout << "Waiting for poll() ..." << std::endl;
		rc = poll(fds, nfds, timeout);

		if(rc < 0)
		{
			perror("  poll() failed");
			break;
		}
		else if(rc == 0)
		{
			perror("  poll() timed out.  End program.");
			break;
		}
		current_size = nfds;
		for(int i = 0; i < current_size; i++)
		{
			if(fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN)
			{
				// perror("  Error! revents = " , fds[i].revents);
				end_server = true;
				break;
			}
			if(fds[i].fd == sock)
			{
				std::cout << " Listening socket is readable" << std::endl;
				do
				{
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
					std::cout << " New incoming connection - " << connection << std::endl;
					fds[nfds].fd = connection;
					fds[nfds].events = POLLIN;
					nfds++;
				}while(connection != -1);
			}
			else
			{
				std::cout << " Descriptor " << fds[i].fd << " is readable" << std::endl;
				close(fds[i].fd);
				fds[i].fd = -1;
				end_server = true;
			}
			
		}


	}
}



void HDE::SocketHde::test_connection(int item_to_test)
{
	if(item_to_test < 0)
	{
		perror("Failled to connect...");
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