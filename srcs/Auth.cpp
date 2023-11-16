#include "../includes/Client.hpp"
#include "../includes/Args.hpp"
#include <vector>
#include "../includes/Replies.hpp"
#include "../includes/Channel.hpp"
#include "../includes/socket.hpp"
#include <algorithm>
#include <cctype>

bool HDE::SocketHde::isFound(const std::vector<std::string> &vec, const std::string &str)
{
	for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if (*it == str)
		{
			return true; // The string exists in the vector
		}
	}
	return false; // The string does not exist in the vector
}

bool HDE::SocketHde::commands(std::vector<std::string> message, std::vector<std::pair<std::string, std::string  > > joinVector, int i)
{
	if (message[0].compare("PASS") == 0)
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_ALREADYREGISTRED(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}

	if (message[0].compare("USER") == 0)
	{
		if (CheckUSER(message, clt.at(fds[i].fd), i))
		{
			return true;
		}
		return false;
	}
	else if (message[0].compare("NICK") == 0)
	{
		if (CheckNICK(message, clt.at(fds[i].fd), i))
		{
			return true;
		}
		return false;
	}
	else if (message[0].compare("JOIN") == 0)
	{
		Join(joinVector, i);
		return false;
	}
	else if (message[0].compare("PART") == 0)
	{
		Part(message, i);
	}

	else if (message[0].compare("TOPIC") == 0)
	{
		Topic(message, i);
	}
	else if (message[0].compare("PRIVMSG") == 0)
	{
		Privmsg(message, i);
	}
	else if (message[0].compare("BOT") == 0)
	{
		Bot(i);
	}

	else if (message[0].compare("MODE") == 0)
	{
		std::cout << "Entred MODE Command\n";
		if (CheckMODE(message, i))
		{
			std::cout << "MODE Command Success" << std::endl;
			return true;
		}
		else
		{
			std::cout << "SIGNED==>MODE ERROR" << std::endl;
			return false;
		}
	}
	else if (message[0].compare("KICK") == 0)
	{
		if (CheckKICK(message, i))
		{
			std::cout << "Kick Command Success" << std::endl;
			for (int j = 0; j < channelsMap.at(message[1])->getUsers().size(); j++)
			{
				std::cout << "User in the channel are: " << channelsMap.at(message[1])->getUsers()[j].getNickname() << std::endl;
			}
			return true;
		}
		else
		{
			std::cout << "SIGNED==>KICK ERROR" << std::endl;
			return false;
		}
	}
	else if (message[0].compare("INVITE") == 0)
	{
		if (CheckINVITE(message, i))
		{
			std::cout << "INVITE Command Success" << std::endl;
			return true;
		}
		else
		{
			std::cout << "SIGNED==>INVITE ERROR" << std::endl;
			return false;
		}
	}
	return false;
}

bool HDE::SocketHde::Auth(std::vector<std::string> message, std::vector<std::pair<std::string, std::string > > joinVector, int i)
{

	if (!message.empty())
	{
		std::string &secondElement = message[0];
		if (!secondElement.empty())
		{
			std::transform(secondElement.begin(), secondElement.end(), secondElement.begin(), ::toupper);
		}
		if (clt.at(fds[i].fd).getIsSignedIn() == false)
		{
			if (message[0].compare("PASS") != 0)
			{
				sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOTREGISTERED(), clt.at(fds[i].fd).getClientId());
				return false;
			}
			if (CheckPASS(message, clt.at(fds[i].fd), password, i))
			{
				clt.at(fds[i].fd).setIsSignedIn(true);
				return true;
			}
			return false;
		}
		else if (clt.at(fds[i].fd).getIsSignedIn() == true)
		{
			if (clt.at(fds[i].fd).isSettingsSetted() == true)
			{
				if (commands(message, joinVector, i))
					return true;
				return false;
			}
			if (clt.at(fds[i].fd).isSettingsSetted() == false)
			{
				// if (message[0].compare("PASS") == 0)
				// {
				// 	sendMessage(":" + localhost + ERR_ALREADYREGISTRED(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
				// 	return false;
				// }
				if (message[0].compare("USER") == 0)
				{
					if (CheckUSER(message, clt.at(fds[i].fd), i))
					{
						if (clt.at(fds[i].fd).getNFlag() == true && clt.at(fds[i].fd).getUFlag() == true && clt.at(fds[i].fd).isSettingsSetted() == false)
						{
							sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + RPL_WELCOME(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
							clt.at(fds[i].fd).setIsSettingsSetted(true);
						}
						return true;
					}
				}
				else if (message[0].compare("NICK") == 0)
				{
					if (CheckNICK(message, clt.at(fds[i].fd), i))
					{
						AllUsers.insert(std::pair<std::string, int>(clt.at(fds[i].fd).getNickname(), i));
						if (clt.at(fds[i].fd).getNFlag() == true && clt.at(fds[i].fd).getUFlag() == true && clt.at(fds[i].fd).isSettingsSetted() == false)
						{
							sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + RPL_WELCOME(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
							clt.at(fds[i].fd).setIsSettingsSetted(true);
						}
						// std::cout << "Nickname is : " << clt.at(fds[i].fd).getNickname() << std::endl;
						return true;
					}
					return false;
				}
				else
				{
					sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOTREGISTERED(), clt.at(fds[i].fd).getClientId());
					return false;
				}
			}
		}
	}
	return true;
}
