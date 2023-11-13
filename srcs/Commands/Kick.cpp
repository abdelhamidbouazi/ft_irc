#include "../../includes/socket.hpp"

bool HDE::SocketHde::CheckKICK(std::vector<std::string> message, int i)
{
	if (message.size() != 3){
		std::cout << "args error" <<std::endl;
		return false;
	}
	if (channelsMap.empty())
	{
		std::cout << "KICK: Empty list of channels" << std::endl;
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
		if (channelsMap.find(message[1]) != channelsMap.end())
		{
			int user;
			if (Client::getIdByUsername(message[2]) == -1)
			{
				std::cout << "KICK: User not Found" << std::endl;
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
						std::cout << "KICK: User erased from the channel" << std::endl;
						return true;
					}
				}
			}
		}
		else
		{
			std::cout << "KICK: channel Key not found in the map" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "KICK: You are not operator" << std::endl;
		return false;
	}
	return false;
}

