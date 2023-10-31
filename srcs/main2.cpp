#include "../includes/Args.hpp"
#include "../includes/Client.hpp"


int main(int ac, char **av){

	if (ac != 3)
	{
		std::cout << "Error: Check Arguments;" << std::endl;
		return 1;
	}
	try {
		Args	a(av[1], av[2]);
		Client	c(5);

		c.addUser("abouazi", c);

		Server(a.getPort(), a.getPassword());
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}