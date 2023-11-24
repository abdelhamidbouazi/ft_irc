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
    int backlog = 10;
    int binding;
    int listening;

    setPort(port);
    setPassword(password);

    sock = socket(domain, service, protocol);
    test_connection(sock);
    if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
    {
        perror("Failled to set socket to non blocking...");
        close(sock);
        exit(EXIT_FAILURE);
    }
    on = 1;
    rc = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    test_connection(rc);
    binding = bind(sock, (struct sockaddr *)&address, sizeof(address));
    set_connection(binding);
    test_connection(get_connection());
    listening = listen(get_sock(), backlog);
    test_connection(listening);
    start_polling();
}

void HDE::SocketHde::start_polling()
{
    timeout = -1;
    pollfd sfd;
    end_server = false;
    char buffer[1024];
    Client dataClient;

    sfd.fd = sock;
    sfd.events = POLLIN;
    fds.push_back(sfd);
    while (!end_server)
    {
        int rc = poll(&fds[0], fds.size(), timeout);
        if (rc == -1)
        {
            std::cerr << "poll() failed" << std::endl;
            close(sock);
            exit(EXIT_FAILURE);
        }
        else if (fds[0].revents & POLLIN)
        {
            std::cout << "Listening socket is readable" << std::endl;
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int connection = accept(sock, (struct sockaddr *)&client_addr, &client_len);
            if (connection == -1)
            {
                std::cerr << "accept() failed" << std::endl;
                exit(EXIT_FAILURE);
            }
            clt.insert(std::pair<int, Client>(connection, Client(connection)));
            clt.at(connection).setLocalhost(ClientIp(connection));
            pollfd clientfd;
            clientfd.fd = connection;
            clientfd.events = POLLIN;
            fds.push_back(clientfd);
        }
        for (size_t i = 1; i < fds.size(); i++)
        {
            flagQuit = 0;
            if (fds[i].revents & POLLIN)
            {
                memset(buffer, 0, sizeof(buffer));
                int rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                if (rc <= 0)
                {
                    if (rc == 0)
                    {
                        CheckQUIT(i);
                        std::cout << "Connection closed" << std::endl;
                    }
                    else 
                    {
                        std::cerr << "recv() failed" << std::endl;
                        close(fds[i].fd);
                    }
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
                        Auth(obj.getRequest(), obj.getJoinVector(), i);
                        if(flagQuit == 1)
                            break;
                        tmp_message = clt.at(fds[i].fd).commande_str.erase(0, pos + 2);
                        pos = clt.at(fds[i].fd).commande_str.find_first_of("\r\n");
                    }
                    if(flagQuit == 1)
                        break;
                }
            }
        }
    }
}

void HDE::SocketHde::test_connection(int item_to_test)
{
    if (item_to_test < 0)
    {
        perror("Failed to connect...");
        close(sock);
        exit(EXIT_FAILURE);
    }
}

std::string HDE::SocketHde::getHostAdresse()
{
    std::system("ifconfig | grep 'inet ' | awk 'NR==2 {print $2}' > .log");
    std::stringstream ss;
    ss << std::ifstream(".log").rdbuf();
    std::system("rm -f .log");
    return (ss.str().substr(0, ss.str().find('\n')));
}

std::string HDE::SocketHde::ClientIp(int socket)
{
    char buffer[INET_ADDRSTRLEN];
    struct sockaddr_in clientAddress;
    socklen_t addrLen = sizeof(clientAddress);
    std::string localhost;

    if (socket >= 0 && getpeername(socket, (struct sockaddr *)&clientAddress, &addrLen) == 0)
    {
        if (inet_ntop(AF_INET, &clientAddress.sin_addr, buffer, INET_ADDRSTRLEN))
        {
            localhost = buffer;
            if (localhost == "127.0.0.1")
                localhost = getHostAdresse();
            // std::cout << "Client IP is : " << localhost << std::endl;
            // std::cout << "Client port is : " << ntohs(clientAddress.sin_port) << std::endl;
            return localhost;
        }
        else
        {
            perror("inet_ntop() failed");
            return NULL;
        }
    }
    else
    {
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
void HDE::SocketHde::sendMessage(std::string message, int fd)
{
    send(fd, message.c_str(), message.length(), 0);
}

void HDE::SocketHde::CleanQuit(std::string nickname, int i)
{
    AllUsers.erase(nickname);
    clt.erase(fds[i].fd);
    close(fds[i].fd);
    fds.erase(fds.begin() + i);
}
