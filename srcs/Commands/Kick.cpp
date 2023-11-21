#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"

bool HDE::SocketHde::CheckKICK(std::vector<std::string> message, int i)
{
	if (message.size() < 3 || message.size() > 5)
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("KICK", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	if (CheckChannelsMap(message, 1) == false || channelsMap.empty())
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}

	std::string nickname = clt.at(fds[i].fd).getNickname();
	bool isOperator = checkUserInChannelOperator(channelsMap.at(message[1]), nickname);

	if (Client::CheckUser(message, 2) == false)
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHNICK(clt.at(fds[i].fd).getNickname(), message[2]), clt.at(fds[i].fd).getClientId());
		return false;
	}

	if (isOperator)
	{
		int user = Client::getIdByUsername(message[2]);
		if (user >= 3)
		{
			std::vector<Client>::iterator it;
			for (it = channelsMap.at(message[1])->getUsers().begin(); it != channelsMap.at(message[1])->getUsers().end(); ++it)
			{
				if (it->getNickname() == message[2])
				{
					// check if the user is that we want to delete is an operator, if operator delete from the vector of operators and users
					channelsMap.at(message[1])->eraseUser(clt.at(user));
					channelsMap.at(message[1])->eraseOperator(clt.at(user));
					if (!message[3].empty())
					{
						std::string rep = ":" + clt.at(fds[i].fd).getNickname()  + "!" + clt.at(fds[i].fd).getNickname() + "@" + clt.at(fds[i].fd).getLocalhost() + " KICK " +  message[1] + " " + message[2] + " "  + message[3] + "\r\n";
						sendMessage(rep, clt.at(user).getClientId());
					}
					else
					{
						std::string rep = ":" + clt.at(fds[i].fd).getNickname()  + "!" + clt.at(fds[i].fd).getNickname() + "@" + clt.at(fds[i].fd).getLocalhost() + " KICK " +  message[1] + " " + message[2] + "\r\n";
						sendMessage(rep, clt.at(user).getClientId());
					}
					return true;
				}
			}
				return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_CHANOPRIVSNEEDED(channelsMap.at(message[1])->getChannelName()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	return false;
}
