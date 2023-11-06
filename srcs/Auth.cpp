#include "../includes/Client.hpp"
#include "../includes/Args.hpp"
#include <vector>
#include "../includes/Replies.hpp"
#include "../includes/Channel.hpp"
#include "../includes/socket.hpp"
#include <algorithm>
#include <cctype>

bool CheckMODE(std::vector<std::string> message, Client &c, std::map<std::string, Channel&> channelsMap);

bool isFound(const std::vector<std::string>& vec, const std::string& str) {
    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        if (*it == str) {
            return true; // The string exists in the vector
        }
    }
    return false; // The string does not exist in the vector
}

int CheckPASS(std::vector <std::string> message, Client	&c, std::string Pass){
	std::string commandPass = "PASS";
	if (message[0] != commandPass || message.size() != 2)
	{
		std::cout << "Enter Password First\n";
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	if (message[1] != Pass){
		Replies::WRONGPASSWORD(c);
		return 0;
	}
	else
		return 1;
}


int CheckUSER(std::vector <std::string> message, Client	&c){
	// std::vector<std::string>::iterator  it;
	bool registred = false;

	if (isFound(c.getUsers(), message[1]))
		registred = true;
	if (message.size() !=  5)
	{
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}

	if (message[1].length() == 0) {
		// Username length error
		return 0;
	}

	if (message[2] != "0")
		c.setMode(true);
	else if (message[2] == "0") {
		c.setMode(false);
	}
	// else if (isdigit(message)) {
		// check if its digit or not
	// }

	// if (it == message.end()) {
	// 	Replies::ERR_ALREADYREGISTRED(c);
	// 	return 0;
	// }
	if (registred == true) {
		Replies::ERR_ALREADYREGISTRED(c);
		return 0;
	}
	else {
		c.addUser(message[1], c);
		c.setFullName(message[4]);
		c.setUFlag();
		return 1;
	}
	return 0;
}

int CheckNICK(std::vector <std::string> message, Client	&c){
	bool registred = false;

	if (isFound(c.getNicknames(), message[1])){
		registred = true;
	}
	if (message.size() != 2)
	{
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	if (registred == true){
		Replies::ERR_ALREADYREGISTRED(c);
		return 0;
	}
	else if (isdigit(message[1][0]))
	{
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	else {
		c.setNickname(message[1]);
		c.setNFlag();
		return 1;
	}
	return 0;
}

bool commands(std::vector<std::string> message, Client &c, std::map<std::string, Channel&> channelsMap, std::vector<std::pair<std::string , std::string > > joinVector)
{
	Channel ch("channel1", c);
	// Channel ch;
	if (message[0].compare("USER") == 0)
	{
		if (CheckUSER(message, c)) {
			std::cout << "SIGNED==>Username is: " << c.getUsername() << "\nFullname is: " << c.getFullName() << std::endl;
			return true;
		}
		return false;
	}
	else if (message[0].compare("NICK") == 0)
	{
		if (CheckNICK(message, c)) {
			std::cout << "SIGNED==>Nickname is : " << c.getNickname() << std::endl;
			return true;
		}
		return false;
	}
	else if (message[0].compare("JOIN") == 0)
	{
		// if (CheckNICK(message, c)) {
		// 	// std::cout << "SIGNED==>Nickname is : " << c.getNickname() << std::endl;
		// 	return true;
		// }
		// return false;
		Join(joinVector, c, channelsMap);
		std::cout << "SIGNED==>Entred JOIN Command Function\n";
	}
	else if (message[0].compare("MODE") == 0)
	{
		if (CheckMODE(message, c, channelsMap)) {
	// 		std::cout << "SIGNED==>Nickname is : " << c.getNickname() << std::endl;
	// 		return true;
	// 	}
			return false;
		}
		else {
			std::cout << "SIGNED==>Enter a valid Command" << std::endl;
			return false;
		}
	}
	return false;
}

bool	Auth(std::vector<std::string> message, Client &c, std::string Password, std::map<std::string, Channel&> channelsMap, std::vector<std::pair<std::string , std::string > > joinVector)
{

	if (message.size() > 1) {
        std::string& secondElement = message[0];
        if (!secondElement.empty()) {
            std::transform(secondElement.begin(), secondElement.end(), secondElement.begin(), ::toupper);
        }
    }

	if (message.size() < 2)
		return false;

	if (c.getIsSignedIn() == false) {
		if (CheckPASS(message, c, Password)){
			std::cout << "Command Pass Passed With Success" << std::endl;
			c.setIsSignedIn(true);
			return true;
		}
		return false;
	}
	else if (c.getIsSignedIn() == true) {

		if (c.getNFlag() && c.getUFlag()) {
			c.setIsSettingsSetted(true);
		}
		if (c.isSettingsSetted() == true){
			if (commands(message, c, channelsMap, joinVector))
				return true;
			return false;
		}
		if (c.isSettingsSetted() == false) {
			if (message[0].compare("USER") == 0){
				if (CheckUSER(message, c)) {
					std::cout << "username is: " << c.getUsername() << "\nfullname is: " << c.getFullName() << std::endl;
					return true;
				}
			}
			else if (message[0].compare("NICK") == 0) {
				if (CheckNICK(message, c)) {
					std::cout << "Nickname is : " << c.getNickname() << std::endl;
					return true;
				}
				return false;
			}
			else {
				std::cout << "Please set user and nickname first" << std::endl;
				return false;
			}
		}
	}

	// std::string welcomeMessage = "User created succefully : " + c.getUsername() + "\n Your name is : " \
	// 		+ c.getFullName() + "\nAnd nickname is : " + c.getNickname() + "\n";
	// if (c.getCounter() == 3){
	// 	send(c.getClientId(),welcomeMessage.c_str(),welcomeMessage.length(),0);
	// 	c.incrementCounter();
	// }2
	return true;
}

