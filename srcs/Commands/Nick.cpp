#include "../../includes/socket.hpp"

int HDE::SocketHde::CheckNICK(std::vector<std::string> message, Client &c)
{
	bool registred = false;

	if (isFound(c.getNicknames(), message[1]))
	{
		registred = true;
	}
	if (message.size() != 2)
	{
		// Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	if (registred == true)
	{
		// Replies::ERR_ALREADYREGISTRED(c);
		return 0;
	}
	else if (isdigit(message[1][0]))
	{
		// Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	else
	{
		if (c.getNickname() != "")
			c.eraseNickname(c);
		c.setNickname(message[1]);
		c.setNFlag();
		return 1;
	}
	return 0;
}
