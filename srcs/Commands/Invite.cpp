#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"

// bool isUserOperator(Client ctl, std::string user)
// {
// 	return ctl.getUsername() == user;
// }

void HDE::SocketHde::CheckINVITE(std::vector<std::string> message, int i)
{
	if (message.size() != 3)
	{
		sendMessage(":" + clt.at(fds[i].fd).getNickname() + ERR_NEEDMOREPARAMS("INVITE", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return ;
	}
	if (CheckChannelsMap(message, 2) == false || channelsMap.empty())
	{
		sendMessage(":" + clt.at(fds[i].fd).getNickname() + ERR_NOSUCHCHANNEL(message[2], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return ;
	}
	std::string nickname = clt.at(fds[i].fd).getNickname();

	if (Client::CheckUser(message, 1) == false)
	{
		sendMessage(":" + clt.at(fds[i].fd).getNickname() + ERR_NOSUCHNICK(clt.at(fds[i].fd).getNickname(), message[1]), clt.at(fds[i].fd).getClientId());
		return ;
	}

	bool isOperator = checkUserInChannelOperator(channelsMap.at(message[2]), nickname);
	if (isOperator)
	{
		int user;
		std::cout << "debug 1\n";
		if (Client::getIdByUsername(message[1]) >= 3)
		{
			int user = Client::getIdByUsername(message[1]);
			if (checkUserInChannel(channelsMap.at(message[2]), message[1]) == true){
				sendMessage(":" + clt.at(fds[i].fd).getNickname() + ERR_USERONCHANNEL(clt.at(fds[i].fd).getNickname(), channelsMap.at(message[2])->getChannelName()), clt.at(fds[i].fd).getClientId());
				return ;
			}
			channelsMap.at(message[2])->addInvited(clt.at(user));
			sendMessage(":" + clt.at(fds[i].fd).getNickname() + " INVITE " + clt.at(user).getNickname() + " " + channelsMap.at(message[2])->getChannelName() + "\r\n", clt.at(user).getClientId());
		}
	}
	else
		sendMessage(":" + clt.at(fds[i].fd).getNickname() + ERR_CHANOPRIVSNEEDED(channelsMap.at(message[2])->getChannelName()), clt.at(fds[i].fd).getClientId());
}
