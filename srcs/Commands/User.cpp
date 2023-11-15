#include "../../includes/socket.hpp"


int HDE::SocketHde::CheckUSER(std::vector<std::string> message, Client &c)
{
	// std::vector<std::string>::iterator  it;
	bool registred = false;

	if (isFound(c.getUsers(), message[1]))
		registred = true;
	if (message.size() != 5)
	{
		// Replies::NOTENOUGHPARAMS(c);
		return 0;
	}

	if (message[1].length() == 0)
	{
		// Username length error
		return 0;
	}

	if (message[2] != "0" )
		c.setMode(true);
	else if (message[2] == "0")
	{
		c.setMode(false);
	}
	if (registred == true)
	{
		// Replies::ERR_ALREADYREGISTRED(c);
		return 0;
	}
	else
	{
		c.addUser(message[1], c);
		c.setFullName(message[4]);
		c.setUFlag();
		return 1;
	}
	return 0;
}
