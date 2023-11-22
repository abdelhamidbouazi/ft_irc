#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"

void HDE::SocketHde::sendMessageToAllForQuit(int i, std::string channelname)
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
                if(itt->getNickname() != clt.at(fds[i].fd).getNickname())
                    add.push_back(itt->getClientId());
            }
            std::string nick = clt.at(fds[i].fd).getNickname();
            std::string selfStr = ":" + nick  + "!" + nick + "@" + clt.at(fds[i].fd).getLocalhost() + " QUIT " +  channelname + "\r\n";
            for(size_t index = 0; index < add.size() ; index++)
                sendMessage(selfStr, add.at(index));
        }
    }
}

void HDE::SocketHde::CheckQUIT(int i)
{
	bool isJoindToChannels = false;
	std::string nickname = clt.at(fds[i].fd).getNickname();
	// int user = fds[i].fd;
	//check if he is member in any channel using users in channels;

	std::map<std::string, Channel*>::iterator it;

	for (it = channelsMap.begin(); it != channelsMap.end(); it++){
		for (size_t j = 0; j < it->second->getUsers().size(); j++) {
			if (it->second->getUsers().at(j).getNickname() == clt.at(fds[i].fd).getNickname()){
				isJoindToChannels = true;
			}
		}
	}

	if (channelsMap.empty() || isJoindToChannels == false)
	{
		sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + RPL_QUIT(" QUIT"), clt.at(fds[i].fd).getClientId());
		clt.at(fds[i].fd).eraseNickname(clt.at(fds[i].fd));
		clt.at(fds[i].fd).eraseUser(clt.at(fds[i].fd));
		clt.at(fds[i].fd).removeUserFromMap(nickname);
		CleanQuit(clt.at(fds[i].fd).getNickname(), i);
		flagQuit = 1;
	}
	else
	{
		std::map<std::string, Channel*>::iterator it;
		for (it = channelsMap.begin(); it != channelsMap.end(); it++){
			if (checkUserInChannel(it->second, clt.at(fds[i].fd).getNickname())){
				sendMessageToAllForQuit(i, it->second->getChannelName());
				if(it->second->getHasOwner() &&  clt.at(fds[i].fd).getNickname() == it->second->getOwner())
				{
					it->second->setHasOwner(false);
					it->second->setOwner("");
				}
				it->second->eraseUser(clt.at(fds[i].fd));
				if (checkUserInChannelOperator(it->second, clt.at(fds[i].fd).getNickname())) {
					it->second->eraseOperator(clt.at(fds[i].fd));
				}
			}
		}
		clt.at(fds[i].fd).eraseNickname(clt.at(fds[i].fd));
		clt.at(fds[i].fd).eraseUser(clt.at(fds[i].fd));
		clt.at(fds[i].fd).removeUserFromMap(nickname);
		CleanQuit(clt.at(fds[i].fd).getNickname(), i);
		std::cout << "joined to channels and channels not empty\n";
		flagQuit = 1;
	}
}

// User* user = identifyUser(fds[i].fd); // You need to implement this function

// client.removeUser(user); // You need to implement this function

// for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
//     it->removeUser(user); // You need to implement this function
//     if (it->isOperator(user)) { // You need to implement this function
//         it->removeOperator(user); // You need to implement this function
//     }
// }
