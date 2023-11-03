#include "../includes/Args.hpp"
#include "../includes/Client.hpp"
#include "../includes/TestServer.hpp"


int main(int ac, char **av){

	if (ac != 3)
	{
		std::cout << "Error: Check Arguments;" << std::endl;
		return 1;
	}
	try {
		Args	a(av[1], av[2]);
		Client	c(5);

		c.addUser("abdelhamidb1", c);

		// Server(a.getPort(), a.getPassword());
		HDE::TestServer ts(a.getPort(), a.getPassword());
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
