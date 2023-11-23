#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"

void HDE::SocketHde::sendMessageToAllForKick(int i, std::string channelname, std::string message, std::string _nickname)
{
    std::map<std::string, Channel*>::iterator it;
    for(it = channelsMap.begin(); it != channelsMap.end() ; ++it)
    {
        if(it->first == channelname)
        {
            std::vector<Client> tmp = it->second->getUsers();
            std::vector<int > add;
            std::vector<Client>::iterator itt;
            for(itt = tmp.begin(); itt != tmp.end(); itt++)
            {
                // if(itt->getNickname() != clt.at(fds[i].fd).getNickname())
                    add.push_back(itt->getClientId());
            }
            std::string nick = clt.at(fds[i].fd).getNickname();
			std::string selfStr;
			if (message == "") {
            	selfStr = ":" + nick  + "!" + nick + "@" + clt.at(fds[i].fd).getLocalhost() + " KICK " +  channelname + " " + _nickname + " :Kicked from the channel" + "\r\n";
            	for(size_t index = 0; index < add.size() ; index++)
                	sendMessage(selfStr, add.at(index));
			}
			else {
            	selfStr = ":" + nick  + "!" + nick + "@" + clt.at(fds[i].fd).getLocalhost() + " KICK " +  channelname + " " + _nickname + " :" + message + "\r\n";
            	for(size_t index = 0; index < add.size() ; index++)
                	sendMessage(selfStr, add.at(index));
			}
        }
    }
}

bool HDE::SocketHde::CheckKICK(std::vector<std::string> message, int i)
{
	// std::cout
	if (message.size() < 3 || message.size() > 5)
	{
		// sendMessageToAllForKick(i, );
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("KICK", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}
	if (CheckChannelsMap(message, 1) == false || channelsMap.empty())
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
		return false;
	}

	std::string nickname = clt.at(fds[i].fd).getNickname();
	bool isOperator = checkUserInChannelOperator(channelsMap.at(message[1]), nickname);

	if (Client::CheckUser(message, 2) == false)
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHNICK(clt.at(fds[i].fd).getNickname(), message[2]), clt.at(fds[i].fd).getClientId());
		return false;
	}

	if (isOperator)
	{
		int user = Client::getIdByUsername(message[2]);
		if (user >= 3)
		{
			std::vector<Client>::iterator it;
			for (it = channelsMap.at(message[1])->getUsers().begin(); it != channelsMap.at(message[1])->getUsers().end(); ++it)
			{
				if (it->getNickname() == message[2])
				{
					if(channelsMap.at(message[1])->getHasOwner() &&  clt.at(fds[i].fd).getNickname() == channelsMap.at(message[1])->getOwner())
                    {
                        channelsMap.at(message[1])->setHasOwner(false);
                        channelsMap.at(message[1])->setOwner("");
                    }
					// check if the user is that we want to delete is an operator, if operator delete from the vector of operators and users
					channelsMap.at(message[1])->eraseUser(clt.at(user));
					channelsMap.at(message[1])->eraseOperator(clt.at(user));
					if (!message[3].empty())
					{
						std::string rep = ":" + clt.at(fds[i].fd).getNickname()  + "!" + clt.at(fds[i].fd).getNickname() + "@" + clt.at(fds[i].fd).getLocalhost() + " KICK " +  message[1] + " " + message[2] + " "  + message[3] + "\r\n";
						sendMessageToAllForKick(i, message[1], message[3], clt.at(user).getNickname());
						sendMessage(rep, clt.at(user).getClientId());
					}
					else
					{
						std::string rep = ":" + clt.at(fds[i].fd).getNickname()  + "!" + clt.at(fds[i].fd).getNickname() + "@" + clt.at(fds[i].fd).getLocalhost() + " KICK " +  message[1] + " " + message[2] + "\r\n";
						sendMessageToAllForKick(i, message[1], "", clt.at(user).getNickname());
						sendMessage(rep, clt.at(user).getClientId());
					}
					return true;
				}
			}
				return false;
		}
		else
		{
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
