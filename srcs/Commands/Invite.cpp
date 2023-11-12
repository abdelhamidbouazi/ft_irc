#include "../../includes/socket.hpp"

// bool isUserOperator(Client ctl, std::string user)
// {
// 	return ctl.getUsername() == user;
// }

bool HDE::SocketHde::CheckINVITE(std::vector<std::string> message, int i)
{
	if (message.size() != 3){
		std::cout << "args error" <<std::endl;
		return false;
	}
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
				// check if he is user or not
				std::vector<Client>::iterator it;
				for (it = channelsMap.at(message[2])->getUsers().begin(); it != channelsMap.at(message[2])->getUsers().end(); ++it)
				{
					if (it->getUsername() == clt.at(user).getUsername())
					{
						std::cout << "INVITE: User is already a user in the channel" << std::endl;
						return false;
					}
				}
				channelsMap.at(message[2])->addInvited(clt.at(user));
				for (int j = 0; j < channelsMap.at(message[2])->getInvitedUser().size(); j++)
				{
					std::cout << "Invited Users are : " << channelsMap.at(message[2])->getInvitedUser().at(j) << std::endl;
				}
				return true;
			}
		}
		else
		{
			std::cout << "INVITE: channel Key not found in the map" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "INVITE: You are not operator" << std::endl;
		return false;
	}
	return false;
}
