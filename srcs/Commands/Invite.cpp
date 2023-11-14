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
	std::string user = clt.at(fds[i].fd).getUsername();

	
	bool isOperator = checkUserInChannelOperator(channelsMap.at(message[2]), user);
	if (isOperator)
	{
		if (channelsMap.find(message[2]) != channelsMap.end())
		{
			int user;
			std::cout << "debug 1\n";
			if (Client::getIdByUsername(message[1]) == -1)
			{
				std::cout << "INVITE: User not Found" << std::endl;
				return false;
			}
			else if (Client::getIdByUsername(message[1]) >= 3)
			{
				int user = Client::getIdByUsername(message[1]);
				std::vector<Client> cl = channelsMap.at(message[2])->getUsers();
				for(int index = 0 ; index < cl.size() ; index++)
				{
					if (cl[i].getUsername() == clt.at(user).getUsername())
					{
						std::cout << "INVITE: User is already a user in the channel" << std::endl;
						return false;
					}
				}

				channelsMap.at(message[2])->addInvited(clt.at(user));
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
