#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"
#include <algorithm>

bool checkModeArgs(std::vector<std::string> message)
{
	// std::cout << "The message size is : " << message.size() << std::endl;
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
	else if (checker == 'k' || checker == 'o')
	{
		if (message.size() == 5)
			return true;
		return false;
	}
	else if (checker == 'l')
	{
		if (message[2].compare("+"))
		{
			if (message.size() == 5)
				return true;
		}
		if (message[2].compare("-"))
		{
			if (message.size() == 4)
				return true;
		}
		return false;
	}
	return false;
}

bool HDE::SocketHde::modeI(std::vector<std::string> message, int mode, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
		{
			channelsMap.at(message[1])->setInviteOnly(true);
			return true;
		}
		if (mode == 0)
		{
			channelsMap.at(message[1])->setInviteOnly(false);
			return true;
		}

		return false;
	}
	else
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
}

bool HDE::SocketHde::modeT(std::vector<std::string> message, int mode, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1])->setIsTopic(false);
		if (mode == 0)
			channelsMap.at(message[1])->setIsTopic(true);
		return true;
	}
	else
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
}

bool HDE::SocketHde::modeK(std::vector<std::string> message, int mode, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end() && message[1].at(0) == '#')
	{
		if (mode == 1)
			channelsMap.at(message[1])->setKey(message[4]);
		if (mode == 0)
			channelsMap.at(message[1])->setKey("");
		return true;
	}
	else
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
}

bool HDE::SocketHde::modeO(std::vector<std::string> message, int mode, int user, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end() && message[1].at(0) == '#')
	{
		if (mode == 1)
		{
			if (channelsMap.at(message[1])->addOperators(clt.at(user)))
			{
				sendMessage(":@" + clt.at(fds[i].fd).getNickname() + " Added you operator to " + channelsMap.at(message[1])->getChannelName() + " " + clt.at(user).getNickname() + "\r\n", clt.at(user).getClientId());
				return true;
			}
			else
			{
				sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_USERNOTINCHANNEL(clt.at(fds[i].fd).getNickname(), channelsMap.at(message[1])->getChannelName()), clt.at(fds[i].fd).getClientId());
				return false;
			}
		}
		if (mode == 0)
		{
			sendMessage(":@" + clt.at(fds[i].fd).getNickname() + "Remove your operator mode from " + channelsMap.at(message[1])->getChannelName() + " " + clt.at(user).getNickname(), clt.at(user).getClientId());
			channelsMap.at(message[1])->eraseOperator(clt.at(user));
			return true;
		}
	}
	else
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	return false;
	// std::cout << "DEBUG2" << std::endl;
}

bool HDE::SocketHde::modeL(std::vector<std::string> message, int mode, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end() && message[1].at(0) == '#')
	{
		if (mode == 1 && std::atoi(message[4].c_str()) > 0)
		{
			channelsMap.at(message[1])->setlimitUsers(std::atoi(message[4].c_str()));
			return true;
		}
		if (mode == 0)
		{
			channelsMap.at(message[1])->setlimitUsers(-1);
			return true;
		}
		return false;
	}
	else
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
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
	if (channelsMap.empty())
	{
        sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	if (checkModeArgs(message) == false)
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("MODE", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	if (message[2].compare("+") == 0)
		mode = 1;
	else if (message[2].compare("-") == 0)
		mode = 0;
	else
		return false;

	std::string nickname = clt.at(fds[i].fd).getNickname();


	bool isOperator = checkUserInChannelOperator(channelsMap.at(message[1]), nickname);

	if (isOperator)
	{
		if (message[3].compare("i") == 0)
		{
			if (modeI(message, mode, i))
				return true;
			return false;
		}
		else if (message[3].compare("t") == 0)
		{
			if (modeT(message, mode, i))
				return true;
			return false;
		}
		else if (message[3].compare("k") == 0)
		{
			if (modeK(message, mode, i))
				return true;
			return false;
		}
		else if (message[3].compare("o") == 0)
		{
			int user;
			if (Client::getIdByUsername(message[4]) == -1)
			{
            	sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHNICK(clt.at(fds[i].fd).getNickname() , message[4]), clt.at(fds[i].fd).getClientId());
				return false;
			}
			else
			{
				int user = Client::getIdByUsername(message[4]);
				if (modeO(message, mode, user, i)) {
					return true;
				}
			}
			return false;
		}
		else if (message[3].compare("l") == 0)
		{
			if (modeL(message, mode, i))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			// sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_UNKNOWNMODE(message[3][0], channelsMap.at(message[1])->getChannelName()), clt.at(fds[i].fd).getClientId());
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
