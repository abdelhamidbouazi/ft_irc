#include "../includes/Args.hpp"

Args::Args(std::string port, std::string password)
{
	if (port.length() > 6 || port.length() < 2)
		throw std::length_error("Port length error");
	for (size_t i = 0; i < port.size(); i++){
		if (!isdigit(port[i]))
			throw std::length_error("Bad Port!");
	}
	double portValue = std::atof(port.c_str());
	if (portValue < 0 || portValue > 65535)
		throw std::out_of_range("Invalid Port");
	this->Port = portValue;
	if (password.length() < 6)
		throw std::length_error("Password length error");
	else
		this->Password = password;
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
