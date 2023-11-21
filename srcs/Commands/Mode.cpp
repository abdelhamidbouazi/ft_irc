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
		if (message[2].compare("+") == 0) {
			if (message.size() != 5)
				return false;
			return true;
		}
		else if (message[2].compare("-") == 0) {
			if (message.size() != 4)
				return false;
			return true;
		}
		else
			return false;
	}
	return false;
}

void HDE::SocketHde::modeI(std::vector<std::string> message, int mode, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1){
			channelsMap.at(message[1])->setInviteOnly(true);
			sendMessageToAllForInvite(i, message[1], "+i");
		}
		else if (mode == 0){
			channelsMap.at(message[1])->setInviteOnly(false);
			sendMessageToAllForInvite(i, message[1], "-i");
		}
	}
	else
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
}

void HDE::SocketHde::modeT(std::vector<std::string> message, int mode, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1])->setIsTopic(false);
		else if (mode == 0)
			channelsMap.at(message[1])->setIsTopic(true);
	}
	else
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
	return;
}

void HDE::SocketHde::modeK(std::vector<std::string> message, int mode, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
			channelsMap.at(message[1])->setKey(message[4]);
		else if (mode == 0)
			channelsMap.at(message[1])->setKey("");
	}
	else
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
}

void HDE::SocketHde::modeO(std::vector<std::string> message, int mode, int user, int i)
{
	if (channelsMap.find(message[1]) != channelsMap.end())
	{
		if (mode == 1)
		{
			if (channelsMap.at(message[1])->addOperators(clt.at(user)))
				sendMessage(":@" + clt.at(fds[i].fd).getNickname() + " Added you operator to " + channelsMap.at(message[1])->getChannelName() + " " + clt.at(user).getNickname() + "\r\n", clt.at(user).getClientId());
			else
				sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_USERNOTINCHANNEL(clt.at(fds[i].fd).getNickname(), channelsMap.at(message[1])->getChannelName()), clt.at(fds[i].fd).getClientId());
		}
		else if (mode == 0)
		{
			sendMessage(":@" + clt.at(fds[i].fd).getNickname() + " Remove your operator mode from " + channelsMap.at(message[1])->getChannelName() + " " + clt.at(user).getNickname() + "\r\n", clt.at(user).getClientId());
			channelsMap.at(message[1])->eraseOperator(clt.at(user));
		}
	}
	else
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
}

void HDE::SocketHde::modeL(std::vector<std::string> message, int mode, int i)
{

	if (mode == 1 && std::atoi(message[4].c_str()) > 0) {
		std::cout << "Entred ModeL and inside mode1: " << std::atoi(message[4].c_str()) << std::endl;
		channelsMap.at(message[1])->setlimitUsers(std::atoi(message[4].c_str()));
		std::cout << "exited ModeL and inside mode1: " << std::endl;
	}
	else if (mode == 0) {
		std::cout << "Entred ModeL and inside mode0" << std::endl;
		channelsMap.at(message[1])->setlimitUsers(-1);
		std::cout << "exited ModeL and inside mode0" << std::endl;
	}
}

bool isUserOperator(Client ctl, std::string user)
{
	return ctl.getUsername() == user;
}

void HDE::SocketHde::CheckMODE(std::vector<std::string> message, int i)
{

	int mode;
	if (checkModeArgs(message) == false)
	{
		if (message[3].compare("i") != 0 || message[3].compare("t") != 0 || message[3].compare("l") != 0 || message[3].compare("k") != 0 || message[3].compare("o") != 0)
			return ;
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("MODE", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return ;
	}
	if (CheckChannelsMap(message, 1) == false || channelsMap.empty())
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return;
	}

	if (message[2].compare("+") == 0)
		mode = 1;
	else if (message[2].compare("-") == 0)
		mode = 0;
	else
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("MODE", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return;
	}
	std::string nickname = clt.at(fds[i].fd).getNickname();
	bool isOperator = checkUserInChannelOperator(channelsMap.at(message[1]), nickname);

	if (isOperator)
	{
		if (message[3].compare("i") == 0)
		{
			modeI(message, mode, i);
		}
		else if (message[3].compare("t") == 0)
		{
			modeT(message, mode, i);
		}
		else if (message[3].compare("k") == 0)
		{
			modeK(message, mode, i);
		}
		else if (message[3].compare("o") == 0)
		{
			int user;
			if (Client::CheckUser(message, 4) == false)
				sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHNICK(clt.at(fds[i].fd).getNickname(), message[4]), clt.at(fds[i].fd).getClientId());
			else
			{
				int user = Client::getIdByUsername(message[4]);
				modeO(message, mode, user, i);
			}
		}
		else if (message[3].compare("l") == 0)
		{
			std::cout << "Entred the modeL function" << std::endl;
			modeL(message, mode, i);
			std::cout << "Exited the modeL function" << std::endl;
		}
		else
			sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_UNKNOWNMODE(message[3][0], channelsMap.at(message[1])->getChannelName()), clt.at(fds[i].fd).getClientId());
	}
	else
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_CHANOPRIVSNEEDED(channelsMap.at(message[1])->getChannelName()), clt.at(fds[i].fd).getClientId());
	return;
}
