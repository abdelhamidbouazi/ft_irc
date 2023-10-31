#include "../includes/Args.hpp"
#include "../includes/Client.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



std::string receive(int clientSocket) {
    char buffer[1024]; // You can adjust the buffer size as needed
    memset(buffer, 0, sizeof(buffer)); // Clear the buffer

    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived == -1) {
        std::cerr << "Error receiving data: " << std::strerror(errno) << std::endl;
        return "";
    } else {
        return std::string(buffer, bytesReceived);
    }
}

int Server(int Port, std::string Password) {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket: " << std::strerror(errno) << std::endl;
        return 1;
    }

    // Bind the socket to an address and port
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(Port); // Use the port of your choice

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding to address: " << std::strerror(errno) << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening for connections: " << std::strerror(errno) << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port " << Port << " ..." << std::endl;

    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
    Client c(clientSocket);


    if (clientSocket == -1) {
        std::cerr << "Error accepting connection: " << std::strerror(errno) << std::endl;
    }
    // Accept and handle incoming connections
    std::string message;
    std::vector<std::string> USER;
        USER.push_back("USER");
        USER.push_back("abouazi");
        USER.push_back("1");
        USER.push_back("*");
        USER.push_back("Abdelhamid");
        USER.push_back("Bouazi");
    while (true) {
		message = receive(clientSocket);
		// std::cout << message << std::endl;

        Auth(USER, c, Password);
    }
    // Close the server socket (this will not be reached in this example)
    close(serverSocket);

    return 0;
}
