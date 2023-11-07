#include "../includes/socket.hpp"
#include "../includes/Commande.hpp"
#include "../includes/Client.hpp"
#include <string.h>
#include <stdio.h>

HDE::SocketHde::SocketHde(int domain, int service, int protocol, int port, unsigned long interface, std::string password)
{
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);

    setPort(port);
    setPassword(password);

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
    memset(fds, 0, sizeof(fds));
    fds[0].fd = sock;
    fds[0].events = POLLIN;
    timeout = (3 * 60 * 1000);
    end_server = false;
    nfds = 1;
    int current_size = 0;
    char buffer[800];
    int new_sd = -1;

    while (!end_server)
    {
        int rc = poll(fds, nfds, timeout);

        if (rc < 0)
        {
            perror("poll() failed");
            close(sock);
            break;
        }
        else if (rc == 0)
        {
            std::cout << "poll() timed out. End program." << std::endl;
            break;
        }
        else if (fds[0].revents & POLLIN)
        {
            std::cout << "Listening socket is readable" << std::endl;

            int connection = accept(sock, NULL, NULL);
            if (connection < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                    perror("accept() failed");
                    close(sock);
                    end_server = true;
                }
            }
            else
            {
                localhost = ClientIp(connection);
                clt.insert(std::pair<int, Client>(connection, Client(connection)));
                fds[nfds].fd = connection;
                fds[nfds].events = POLLIN;
                nfds++;
            }
        }

        current_size = nfds;
        for (int i = 1; i < current_size; i++) // Start from 1, skipping the listening socket
        {
            if (fds[i].revents & POLLIN)
            {
                memset(buffer, 0, sizeof(buffer));
                int rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                if (rc <= 0)
                {
                    if (rc == 0)
                    {
                        std::cout << "Connection closed" << std::endl;
                    }
                    else if (errno != EWOULDBLOCK)
                    {
                        perror("recv() failed");
                    }

                    close(fds[i].fd);
                    fds[i].fd = -1;
                }
                else
                {
                    Commande obj;
                    std::string tmp_message;
                    std::string msg(buffer);
                    clt.at(fds[i].fd).commande_str += msg;
                    size_t pos = clt.at(fds[i].fd).commande_str.find_first_of("\r\n");
                    while (pos != std::string::npos)
                    {
                        tmp_message = clt.at(fds[i].fd).commande_str.substr(0, pos);
                        obj.start_parssing(tmp_message);

						std::cout << "**** The Client ID is : " << clt.at(fds[i].fd).getClientId() << std::endl;
						if(Auth(obj.getRequest(), obj.getJoinVector(), i)) {

						// if(Auth(obj.getRequest(), clt.at(fds[i].fd), getPassword(), channelsMap, obj.getJoinVector())) {
                            // std::string str = "wellcom to the irc server\n";
							// send(clt.at(fds[i].fd).getClientId(), str.c_str(), str.length(), 0);
						}

                        tmp_message = clt.at(fds[i].fd).commande_str.erase(0, pos + 2);
                        pos = clt.at(fds[i].fd).commande_str.find_first_of("\r\n");
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


void HDE::SocketHde::setPort(int port)
{
    this->port = port;
}

void HDE::SocketHde::setPassword(std::string password)
{
    this->password = password;
}

int HDE::SocketHde::getPort()
{
    return port;
}

std::string HDE::SocketHde::getPassword()
{
    return password;
}

std::string HDE::SocketHde::getLocalhost()
{
    return this->localhost;
}

void HDE::SocketHde::setLocalhost(std::string localhost)
{
    this->localhost = localhost;
}