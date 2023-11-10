#include "../../includes/socket.hpp"

// bool isUserOperator(Client ctl, std::string user)
// {
// 	return ctl.getUsername() == user;
// }

bool HDE::SocketHde::CheckINVITE(std::vector<std::string> message, int i)
{
	if (channelsMap.empty())
	{
		std::cout << "INVITE: Empty list of channels" << std::endl;
		return false;
	}
	std::vector<Client> operators = channelsMap.at(message[2])->getOperators();
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
		if (channelsMap.find(message[2]) != channelsMap.end())
		{
			int user;
			if (Client::getIdByUsername(message[1]) == -1)
			{
				std::cout << "INVITE: User not Found" << std::endl;
				return false;
			}
			else if (Client::getIdByUsername(message[1]) >= 3)
			{
				int user = Client::getIdByUsername(message[1]);
				// ch->addUsers(clt.at(user));
				channelsMap.at(message[2])->addUsers(clt.at(user));
			}
			else
			{
				std::cout << "INVITE: channel Key not found in the map" << std::endl;
				return false;
			}
		}
	}
	else
	{
		std::cout << "INVITE: You are not operator" << std::endl;
		return false;
	}
	return false;
}
