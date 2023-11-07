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

bool HDE::SocketHde::commands(std::vector<std::string> message, std::vector<std::pair<std::string , std::string > > joinVector,int i)
{
	Channel ch("channel1", clt.at(fds[i].fd));
	// Channel ch;
	if (message[0].compare("USER") == 0)
	{
		if (CheckUSER(message, clt.at(fds[i].fd))) {
			std::cout << "SIGNED==>Username is: " << clt.at(fds[i].fd).getUsername() << "\nFullname is: " << clt.at(fds[i].fd).getFullName() << std::endl;
			return true;
		}
		return false;
	}
	else if (message[0].compare("NICK") == 0)
	{
		if (CheckNICK(message, clt.at(fds[i].fd))) {
			std::cout << "SIGNED==>Nickname is : " << clt.at(fds[i].fd).getNickname() << std::endl;
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
		Join(joinVector, i);
		std::cout << "SIGNED==>Entred JOIN Command Function\n";
	}
	else if (message[0].compare("MODE") == 0)
	{
		if (CheckMODE(message, i)) {
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


bool	HDE::SocketHde::Auth(std::vector<std::string> message, std::vector<std::pair<std::string , std::string > > joinVector,int i)
{

	if (message.size() > 1) {
        std::string& secondElement = message[0];
        if (!secondElement.empty()) {
            std::transform(secondElement.begin(), secondElement.end(), secondElement.begin(), ::toupper);
        }
    }

	if (message.size() < 2)
		return false;

	if (clt.at(fds[i].fd).getIsSignedIn() == false) {
		if (CheckPASS(message, clt.at(fds[i].fd), password)){
			std::cout << "Command Pass Passed With Success" << std::endl;
			clt.at(fds[i].fd).setIsSignedIn(true);
			return true;
		}
		return false;
	}
	else if (clt.at(fds[i].fd).getIsSignedIn() == true) {

		if (clt.at(fds[i].fd).getNFlag() && clt.at(fds[i].fd).getUFlag()) {
			clt.at(fds[i].fd).setIsSettingsSetted(true);
		}
		if (clt.at(fds[i].fd).isSettingsSetted() == true){
			if (commands(message, joinVector, i))
				return true;
			return false;
		}
		if (clt.at(fds[i].fd).isSettingsSetted() == false) {
			if (message[0].compare("USER") == 0){
				if (CheckUSER(message, clt.at(fds[i].fd))) {
					std::cout << "username is: " << clt.at(fds[i].fd).getUsername() << "\nfullname is: " << clt.at(fds[i].fd).getFullName() << std::endl;
					return true;
				}
			}
			else if (message[0].compare("NICK") == 0) {
				if (CheckNICK(message, clt.at(fds[i].fd))) {
					std::cout << "Nickname is : " << clt.at(fds[i].fd).getNickname() << std::endl;
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
