#include "../includes/Args.hpp"
#include "../includes/Client.hpp"
#include "../includes/Channel.hpp"
#include "../includes/TestServer.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Error: Check Arguments;" << std::endl;
		return 1;
	}
	try {
		Args	a(av[1], av[2]);
		// HDE::TestServer ts(a.getPort(), a.getPassword());
		// HDE::SimpleServer(AF_INET, SOCK_STREAM, 0, a.getPort(), INADDR_ANY, 10, a.getPassword());
		HDE::ListeningSocket(AF_INET, SOCK_STREAM, 0, a.getPort(), INADDR_ANY, 10, a.getPassword());
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
