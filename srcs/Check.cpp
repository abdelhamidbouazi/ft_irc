#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include "../includes/Replies.hpp"
#include "../includes/socket.hpp"

bool HDE::SocketHde::CheckChannelsMap(std::vector<std::string> message, int place)
{
	// Check if the channel exists in the map
	if (channelsMap.find(message[place]) != channelsMap.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool	Client::CheckUser(std::vector<std::string> message, int place)
{
	for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++) {
		if (*it == message[place])
		{
			return true;
		}
	}
	return false;
}
