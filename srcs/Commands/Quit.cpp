#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"



void HDE::SocketHde::CheckQUIT(int i)
{
	bool isJoindToChannels = false;
	std::string nickname = clt.at(fds[i].fd).getNickname();
	int user = fds[i].fd;
	//check if he is member in any channel using users in channels;

	std::map<std::string, Channel*>::iterator it;

	for (it = channelsMap.begin(); it != channelsMap.end(); it++){
		for (int j = 0; j < it->second->getUsers().size(); j++) {
			if (it->second->getUsers().at(j).getNickname() == clt.at(fds[i].fd).getNickname()){
				isJoindToChannels = true;
			}
		}
	}

	if (channelsMap.empty() || isJoindToChannels == false)
	{
		clt.at(fds[i].fd).eraseNickname(clt.at(fds[i].fd));
		clt.at(fds[i].fd).eraseUser(clt.at(fds[i].fd));
		clt.at(fds[i].fd).removeUserFromMap(nickname);
		CleanQuit(clt.at(fds[i].fd).getNickname(), i);
		std::cout << "NOTJOIN==============================\n";
		flagQuit = 1;
	}
	else
	{
		std::map<std::string, Channel*>::iterator it;
		for (it = channelsMap.begin(); it != channelsMap.end(); it++){
			if (checkUserInChannel(it->second, clt.at(fds[i].fd).getNickname())){
				std::cout << it->second->getLimitUsers() << std::endl;
				if(it->second->getHasOwner() &&  clt.at(fds[i].fd).getNickname() == it->second->getOwner())
				{
					it->second->setHasOwner(false);
					it->second->setOwner("");
				}
				it->second->eraseUser(clt.at(fds[i].fd));
				if (checkUserInChannelOperator(it->second, clt.at(fds[i].fd).getNickname())) {
					it->second->eraseOperator(clt.at(fds[i].fd));
				}
				if(it->second->getLimitUsers() != -1)
                        it->second->setlimitUsers(it->second->getLimitUsers() - 1 );
				std::cout << it->second->getLimitUsers() << std::endl;
				std::cout << "Removed from: " << it->second->getChannelName()<< std::endl;
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
