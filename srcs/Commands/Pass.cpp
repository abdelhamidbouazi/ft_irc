#include "../../includes/socket.hpp"

int HDE::SocketHde::CheckPASS(std::vector<std::string> message, Client &c, std::string Pass)
{
	std::string commandPass = "PASS";
	if (message[0] != commandPass || message.size() != 2)
	{
		// Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	if (message[1] != Pass)
	{
		// Replies::WRONGPASSWORD(c);
		return 0;
	}
	else
		return 1;
}
