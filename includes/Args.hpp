# ifndef ARGS_HPP
# define ARGS_HPP

#include <iostream>
#include <cstring>
#include <sstream>
#include<string>

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
