#include "../includes/Args.hpp"

Args::Args(std::string port, std::string password)
{
	if (port.length() > 6 || port.length() < 2)
		throw std::length_error("Port length error");
	std::istringstream iss(port);
	int portValue;
	if (iss >> portValue)
	{
		if (portValue < 0 || portValue > 65535)
			throw std::out_of_range("Invalid Port");

		this->Port = portValue;

		if (password.length() < 8)
			throw std::length_error("Password length error");
		else
			this->Password = password;
	}
	else
	{
		throw std::length_error("Bad Port!");
	}
}

Args::~Args()
{
}

int Args::getPort()
{
	return this->Port;
}

std::string Args::getPassword()
{
	return this->Password;
}
