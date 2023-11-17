#include "../includes/TestServer.hpp"
#include "../includes/Client.hpp"
#include "../includes/Args.hpp"

HDE::TestServer::TestServer(int port, std::string password) : SimpleServer(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10, password)
{
    std::cout << "Starting server..." << std::endl;
    launch();

}
void HDE::TestServer::accepter()
{
    struct sockaddr_in address = get_socket()->get_address();
    int addrlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
    read(new_socket, buffer, 30000); 
}

void HDE::TestServer::handler()
{
    std::cout << buffer << std::endl;
}

void HDE::TestServer::responder()
{
    char str[] = "Hello from server";
    send(new_socket, str, strlen(str), 0);
    close(new_socket);
}

void HDE::TestServer::launch()
{
    while (1)
    {
        std::cout << "======= Waiting for connection... =======" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "====== Done =======" << std::endl <<std::endl;
    }
}