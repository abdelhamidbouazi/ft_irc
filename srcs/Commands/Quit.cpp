#include "../../includes/socket.hpp"
#include "../../includes/Replies.hpp"



void HDE::SocketHde::CheckQUIT(std::vector<std::string> message, int i)
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
		std::cout << "NOTJOIN==============================\n";
		clt.at(fds[i].fd).eraseNickname(clt.at(fds[i].fd));
		clt.at(fds[i].fd).eraseUser(clt.at(fds[i].fd));
		clt.at(fds[i].fd).removeUserFromMap(nickname);
		CleanQuit(clt.at(fds[i].fd).getNickname(), i);
		std::cout << "NOTJOIN==============================\n";
	}
	else
	{
		std::cout << "joined to channels and channels not empty\n";
	}
	std::cout << "Passed==============================\n";
	// close(user);
	std::cout << "Passed2==============================\n";
}

// User* user = identifyUser(fds[i].fd); // You need to implement this function

// client.removeUser(user); // You need to implement this function

// for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
//     it->removeUser(user); // You need to implement this function
//     if (it->isOperator(user)) { // You need to implement this function
//         it->removeOperator(user); // You need to implement this function
//     }
// }
