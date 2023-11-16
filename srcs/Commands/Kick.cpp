#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"

bool HDE::SocketHde::CheckKICK(std::vector<std::string> message, int i)
{
	if (message.size() < 3 || message.size() > 5){
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("KICK", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	if (channelsMap.empty())
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	std::vector<Client> operators = channelsMap.at(message[1])->getOperators();
	std::string user = clt.at(fds[i].fd).getUsername();
	bool isOperator = false;

	for (std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it)
	{
		if (it->getUsername() == user)
		{
			isOperator = true;
			continue;
		}
	}
	if (isOperator)
	{
		if (channelsMap.find(message[1]) != channelsMap.end() && message[1].at(0) == '#')
		{
			int user;
			if (Client::getIdByUsername(message[2]) == -1)
			{
				sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHNICK(clt.at(fds[i].fd).getNickname() , message[4]), clt.at(fds[i].fd).getClientId());
				return false;
			}
			else if (Client::getIdByUsername(message[2]) >= 3)
			{
				int user = Client::getIdByUsername(message[2]);
				std::vector<Client>::iterator it;
				for (it = channelsMap.at(message[1])->getUsers().begin(); it != channelsMap.at(message[1])->getUsers().end(); ++it)
				{
					if (it->getUsername() == clt.at(user).getUsername())
					{
						// check if the user is that we want to delete is an operator, if operator delete from the vector of operators and users
						channelsMap.at(message[1])->eraseUser(clt.at(user));
						channelsMap.at(message[1])->eraseOperator(clt.at(user));
						if (!message[3].empty()){
							sendMessage(":" + clt.at(fds[i].fd).getNickname() + "KICK " + channelsMap.at(message[1])->getChannelName() + " " + clt.at(user).getNickname() + " :" + message[3], clt.at(user).getClientId());
						}
						else {
							sendMessage(":" + clt.at(fds[i].fd).getNickname() + "KICK " + channelsMap.at(message[1])->getChannelName() + " " + clt.at(user).getNickname(), clt.at(user).getClientId());
						}
						return true;
					}
				}
			}
		}
		else
		{
			sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
			return false;
		}
	}
	else
	{
		// sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_UNKNOWNMODE(message[3][0], channelsMap.at(message[1])->getChannelName()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	return false;
}

