#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"

int HDE::SocketHde::CheckNICK(std::vector<std::string> message, Client &c, int i)
{
	bool registred = false;

	if (isFound(c.getNicknames(), message[1]))
	{
		registred = true;
	}
	if (message.size() != 2)
	{
        sendMessage(":" + localhost + ERR_NEEDMOREPARAMS("NICK", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return 0;
	}
	if (registred == true)
	{
		sendMessage(":" + localhost + ERR_NICKNAMEINUSE(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return 0;
	}
	else if (isdigit(message[1][0]) || message[1].length() < 1)
	{
		sendMessage(":" + localhost + ERR_ERRONEUSNICKNAME(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
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
