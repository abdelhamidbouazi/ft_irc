#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"

bool HDE::SocketHde::CheckMODE(std::vector<std::string> message, int i){


	if (message[0].compare("MODE") == 0)
	{
		if (message[2].compare("+") == 0)
		{
			if (message[3].compare("i") == 0){
				// add the protection for the channels map
				// channelsMap.at(message[1]).setInviteOnly(true);
				// Channel::getChannel(message[1]).setInviteOnly(true);
				return true;
				// clt.at(fds[i].fd).getClientId
			}
			// else if (message[3].compare("t") == 0){
			// 	Channel::getChannel(message[1]).setIsTopic(true);
			// 	return true;
			// }
			// else if (message[3].compare("k") == 0){
			// 	Channel::getChannel(message[1]).setKey(message[4]);
			// 	return true;
			// }
			// else if (message[3].compare("o") == 0){
			// 		Channel::getChannel(message[1]).addOperators(c);
			// 	return true;
			// }
			// else if (message[3].compare("l") == 0){
			// 		// Channel::getChannel(message[1]).setlimitUsers(message[4]); // must be int
			// 	return true;
			// }
			else {
				std::cout << "invalid mode" << std::endl;
			}
		}
		// else if (message[2].compare("-") == 0)
		// {
		// 	if (message[3].compare("i") == 0){
		// 		Channel::getChannel(message[1]).setInviteOnly(false);
		// 		return true;
		// 	}
		// 	else if (message[3].compare("t") == 0){
		// 		Channel::getChannel(message[1]).setIsTopic(false);
		// 		return true;
		// 	}
		// 	else if (message[3].compare("k") == 0){
		// 		Channel::getChannel(message[1]).setKey("");
		// 		return true;
		// 	}
		// 	else if (message[3].compare("o") == 0){
		// 		Channel::getChannel(message[1]).setUsers(c.getUsername(), c);
		// 		return true;
		// 	}
		// 	else if (message[3].compare("l") == 0){
		// 		Channel::getChannel(message[1]).setlimitUsers(-1);
		// 	}
		// 	else {
		// 		std::cout << "invalid mode" << std::endl;
		// 	}
		// }
	}
	std::cout << "MODE" << std::endl;
	return false;
}
