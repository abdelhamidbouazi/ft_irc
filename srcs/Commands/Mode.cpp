#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"
#include <algorithm>
// Channel &getChannel(std::map<std::string, Channel &> channelsMap, std::string channel)
// {
// 	// for (std::vector<std::string>::const_iterator it = channelsMap.begin(); it != channelsMap.end(); ++it) {
// 	//     if (*it == str) {
// 	//         return true; // The string exists in the vector
// 	//     }
// 	// }
// 	// return false;
// 	// std::map<char, int>::iterator it;

// 	// it = mymap.find('b');
// 	// if (it != mymap.end())
// 	// 	mymap.erase(it);
// 	return channelsMap[channel];
// }

bool checkModeArgs(std::vector<std::string> message)
{
	std::cout << "The message size is : " << message.size() << std::endl;
	if (message[3].length() > 2)
	{
		return false;
	}
	char checker = message[3][0];
	if (checker == 'i' || checker == 't')
	{
		if (message.size() == 4)
			return true;
		return false;
	}
	else if (checker == 'k' || checker == 'l' || checker == 'o')
	{
		if (message.size() == 5)
			return true;
		return false;
	}
	else if (checker == 'l'){
		if (message[2].compare("+")){
			if (message.size() == 5)
				return true;
		}
		if (message[2].compare("-")){
			if (message.size() == 4)
				return true;
		}
		return false;
	}
	return false;
}

bool modeI(std::vector<std::string> message, std::map<std::string, Channel &> &channelsMap, int mode)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1]).setInviteOnly(true);
		if (mode == 0)
			channelsMap.at(message[1]).setInviteOnly(false);
		return true;
	}
	else
	{
		std::cout << "Key not found in the map" << std::endl;
		return false;
	}
}

bool modeT(std::vector<std::string> message, std::map<std::string, Channel &> &channelsMap, int mode)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1]).setIsTopic(true);
		if (mode == 0)
			channelsMap.at(message[1]).setIsTopic(false);
		return true;
	}
	else
	{
		std::cout << "Key not found in the map" << std::endl;
		return false;
	}
}

bool modeK(std::vector<std::string> message, std::map<std::string, Channel &> &channelsMap, int mode)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1]).setKey(message[4]);
		if (mode == 0)
			channelsMap.at(message[1]).setKey("");
		return true;
	}
	else
	{
		std::cout << "Key not found in the map" << std::endl;
		return false;
	}
}

bool modeO(std::vector<std::string> message, std::map<std::string, Channel &> &channelsMap, int mode, Client &c)
{
	std::cout << "DEBUG2" << std::endl;
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1]).addOperators(c);
		if (mode == 0)
			channelsMap.at(message[1]).eraseOperator(c);
		return true;
	}
	else
	{
		std::cout << "Key not found in the map" << std::endl;
		return false;
	}
}

bool modeL(std::vector<std::string> message, std::map<std::string, Channel &> &channelsMap, int mode, Client &c)
{
	std::cout << "Entred to the limit users\n";
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		std::cout << "Limit number entred is " << std::atoi(message[4].c_str()) << "\n";
		if (mode == 1 && std::atoi(message[4].c_str()) > 0)
		{
			channelsMap.at(message[1]).setlimitUsers(std::atoi(message[4].c_str()));
			return true;
		}
		if (mode == 0)
		{
			channelsMap.at(message[1]).setlimitUsers(-1);
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "Key not found in the map" << std::endl;
		return false;
	}
}

bool isUserOperator(Client ctl, std::string user)
{
	return ctl.getUsername() == user;
}

bool HDE::SocketHde::CheckMODE(std::vector<std::string> message, int i)
{
	int mode;
	Channel ch("#channel", clt.at(fds[i].fd), "");
	channelsMap.insert(std::pair<std::string, Channel &>("#channel", ch));

	// ch.addUsers(clt.at(fds[4].fd));

	// check if the user is a operator

	if (channelsMap.empty())
	{
		std::cout << "Empty list of channels" << std::endl;
		return false;
	}
	if (checkModeArgs(message) == false)
	{
		std::cout << "args error" << std::endl;
		return false;
	}

	if (message[2].compare("+") == 0)
		mode = 1;
	else if (message[2].compare("-") == 0)
		mode = 0;
	else
		return false;

	std::vector<Client> operators = channelsMap.at(message[1]).getOperators();
	std::string user = clt.at(fds[i].fd).getUsername();
	bool isOperator = false;

	for (std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it)
	{
		if (it->getUsername() == user)
		{
			isOperator = true;
			continue ;
		}
	}

	if (isOperator)
	{
		std::cout << "Access Granted: user is operator" << std::endl;
		// User is an operator, continue with the program
		if (message[0].compare("MODE") == 0)
		{
			if (message[3].compare("i") == 0)
			{
				if (modeI(message, channelsMap, mode))
					return true;
				return false;
				// clt.at(fds[i].fd).getClientId
			}
			else if (message[3].compare("t") == 0)
			{
				if (modeT(message, channelsMap, mode))
					return true;
				return false;
			}
			else if (message[3].compare("k") == 0)
			{
				if (modeK(message, channelsMap, mode))
					return true;
				return false;
			}
			else if (message[3].compare("o") == 0)
			{
					std::cout << "Inisde DEBUG0" << std::endl;
				int user;
				if (Client::getIdByUsername(message[4]) == -1) {
					// std::cout << "User Entred is not found" << std::endl;
					std::cout << "DEBUG3" << std::endl;
					return false;
				}
				else {
					int user = Client::getIdByUsername(message[4]);
					std::cout << user << std::endl;
					// if (clt.at(5).getClientId() > 3){
					// 	std::cout << "clt.at(fds[user])  : " << clt.at(user).getUsername() << std::endl;
					// }
					// maybe check if the user is a user in the channel
					std::cout << "moved " << fds[user].fd<<  std::endl;
					if (modeO(message, channelsMap, mode, clt.at(fds[user].fd))){ // error here in ctl.at(user)
						std::cout << "DEBUG" << std::endl;
						for (int j = 0; j < operators.size(); j++)
						{
							std::cout << "*******====== operators in this channel are : " << operators[j].getClientId() << " username " << operators[j].getUsername() << std::endl;
						}
						return true;
					}
				}
				return false;
			}
			else if (message[3].compare("l") == 0)
			{
				if (modeL(message, channelsMap, mode, clt.at(fds[i].fd)))
				{
					std::cout << "MODE limit users set to : " << channelsMap.at(message[1]).getLimitUsers() << " in channel : " << channelsMap.at(message[1]).getChannelName() << std::endl;
					return true;
				}
				else
				{
					std::cout << "==Error in modeL function" << std::endl;
					return false;
				}
			}
			else
			{
				std::cout << "invalid mode" << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Access denied: user is not operator" << std::endl;
		// User is not an operator, return false
		return false;
	}

	std::cout << "MODE" << std::endl;
	return false;
}
