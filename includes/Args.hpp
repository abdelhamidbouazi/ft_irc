# ifndef ARGS_HPP
# define ARGS_HPP

#include <iostream>
#include <cstring>
#include <sstream>
#include<string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

std::vector<std::string> authC;
authC.push_back("USER");
authC.push_back("NICK");

class Args
{
	private:
		int			Port;
		std::string	Password;
	public:
		Args(std::string port, std::string password);
		~Args();

		int	getPort();
		std::string	getPassword();

};

# endif
