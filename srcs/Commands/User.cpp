#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"


int HDE::SocketHde::CheckUSER(std::vector<std::string> message, Client &c, int i)
{
	bool registred = false;

	if (isFound(c.getUsers(), message[1]))
		registred = true;
	if (message.size() != 5)
	{
        sendMessage(":" + localhost + ERR_NEEDMOREPARAMS("USER", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return 0;
	}

	if (message[1].length() == 0)
	{
        sendMessage(":" + localhost + ERR_NEEDMOREPARAMS("USER", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
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
		sendMessage(":" + localhost + ERR_ALREADYREGISTRED(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
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
