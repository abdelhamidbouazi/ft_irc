#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"

// in the parsing send me the address of channel, and in the vector send
bool CheckMODE(std::vector<std::string> message, Client &c){
	if (message[0].compare("MODE") == 0) {
		for (int i = 0; i < message[3].length(); i++) {
			if (message[3][i].compare('+') != 0 || message[3][i] != "t" || message[3][i] != "k" \
				|| message[3][i] != "o" || message[3][i] != "l")
		if (message[2].compare("+") == 0) {

				if (message[3].compare("i") == 0){
					ch.setInviteOnly(true);
					return true;
				}
				else if (message[3].compare("t") == 0){
					ch.setIsTopic(true);
					return true;
				}
				else if (message[3].compare("k") == 0){
					ch.setKey(message[4]);
					return true;
				}
				else if (message[3].compare("o") == 0){
					ch.setOperators(c.getUsername(), c);
					return true;
				}
				else if (message[3].compare("l") == 0){
					// ch.setlimitUsers(message[4]);
					return true;
				}
				else {
					std::cout << "invalid mode" << std::endl;
				}
			}
		}
		if (message[2].compare("-") == 0) {
			if (message[3].compare("i") == 0){

			}
			else if (message[3].compare("t") == 0){

			}
			else if (message[3].compare("k") == 0){

			}
			else if (message[3].compare("o") == 0){

			}
			else if (message[3].compare("l") == 0){

			}
			else {
				std::cout << "invalid mode" << std::endl;
			}
		}
	}
	std::cout << "MODE" << std::endl;
	return false;
}
