#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"

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
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1]).addOperators(c);
		if (mode == 0)
			channelsMap.at(message[1]).addOperators(c); // remove privelage
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
		// check if the message[4] is an int, if its not int return false
		if (mode == 1)
			channelsMap.at(message[1]).setlimitUsers(std::atoi(message[4].c_str()));
		if (mode == 0)
			channelsMap.at(message[1]).setlimitUsers(-1);
		return true;
	}
	else
	{
		std::cout << "Key not found in the map" << std::endl;
		return false;
	}
}

bool HDE::SocketHde::CheckMODE(std::vector<std::string> message, int i)
{
	int mode;
	Channel ch("#channel", clt.at(fds[i].fd), "");
	channelsMap.insert(std::pair<std::string, Channel &>("#channel", ch));
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
	{
		mode = 1;
	}
	else if (message[2].compare("-") == 0)
	{
		mode = 0;
	}
	else
	{
		return false;
	}
	std::cout << "mode number setted to : " << mode << std::endl;
	for (int j = 0; j < message.size(); j++) {
		std::cout << "**" << message[j] << "**" << std::endl;
	}
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
			if (modeO(message, channelsMap, mode, clt.at(fds[i].fd)))
				return true;
			return false;
		}
		else if (message[3].compare("l ") == 0)
		{
			if (modeL(message, channelsMap, mode, clt.at(fds[i].fd))) {
				std::cout << "MODE limit users set to : " << channelsMap.at(message[1]).getLimitUsers() << " in channel : " << channelsMap.at(message[1]).getChannelName() << std::endl;
				return true;
			}
			return false;
		}
		else
		{
			std::cout << "invalid mode" << std::endl;
		}
	}
	std::cout << "MODE" << std::endl;
	return false;
}
