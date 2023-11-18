#include "../includes/socket.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Error: Check Arguments;" << std::endl;
		return 1;
	}
	try {
		Args	a(av[1], av[2]);
		HDE::SocketHde(AF_INET, SOCK_STREAM, 0, a.getPort(), INADDR_ANY, a.getPassword());
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
