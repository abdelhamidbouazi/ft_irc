#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"

// in the parsing send me the address of channel, and in the vector send
bool CheckMODE(std::vector<std::string> message, Client &c, Channel &ch){
	if (message[0].compare("MODE") == 0) {
		
	}
	std::cout << "MODE" << std::endl;
	return false;
}
