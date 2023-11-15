#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"

int HDE::SocketHde::CheckPASS(std::vector<std::string> message, Client &c, std::string Pass, int i)
{
	std::string commandPass = "PASS";
	if (message[0] != commandPass || message.size() != 2)
	{
    	sendMessage(":" + localhost + ERR_NEEDMOREPARAMS("PASS", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return 0;
	}
	if (message[1] != Pass)
	{
		Replies::WRONGPASSWORD(c);
		return 0;
	}
	else
		return 1;
}
