#include "../includes/Client.hpp"
#include "../includes/Args.hpp"
#include <vector>
#include "../includes/Replies.hpp"
#include <algorithm>

// void splitString(const std::string& input, std::vector<std::string>& tokens) {
//     std::istringstream iss(input);
//     std::string token;

//     while (std::getline(iss, token, ' ')) {
//         tokens.push_back(token);
//     }
// }

// std::string clearSpaces(std::string line)
// {
//     std::string ws = " \n\r\t\f\v";
//     size_t start = line.find_first_not_of(ws);
//     size_t end = line.find_last_not_of(ws) + 1;
//     size_t len = end - start;
//     if(end != 0)
//         line = line.substr(start,len);
//     return line;
// }

int CheckPASS(std::vector <std::string> message, Client	&c, std::string Pass){

	if (message[0] != "PASS" || message.size() != 2)
	{
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
	std::vector<std::string>::iterator  it;

	it = find(message.begin(), message.end(), message[1]); // checking the user if already exist;
	if (message.size() != 6)
	{
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}

	if (message[1].length() > 9) {
		// Username length error
		return 0;
	}

	if (message[2] != "0")
		c.setMode(true);

	if (it != message.end()) {
		Replies::ERR_ALREADYREGISTRED(c);
		return 0;
	}
	else {
		c.addUser(message[1], c);
		c.setFullName(message[4]);
		return 1;
	}
	return 0;
}

// int CheckNICK(std::string message, Client &c){
// 	std::vector<std::string> newM;
// 	splitString(message, newM);
// 	std::vector<std::string>::iterator  it;

// 	it = find(newM.begin(), newM.end(), newM[1]);
// 	newM[1] = clearSpaces(newM[1]);
// 	if (newM.size() != 2)
// 	{
// 		Replies::NOTENOUGHPARAMS(c);
// 		return 0;
// 	}
// 	if(newM[0] == "NICK" && !newM[1].empty()){
// 		if (it == newM.end()){
// 			Replies::ERR_ALREADYREGISTRED(c);
// 		}
// 		else if (isdigit(newM[1][0]))
// 		{
// 			Replies::ERR_ALREADYREGISTRED(c);
// 		}
// 		else {
// 			c.setNickname(newM[1]);
// 			return 1;
// 		}
// 	}

// 	return 0;
// }

bool commands(std::vector<std::string> message, Client &c) {
	(void)c;
	(void)message;
	return false;
}

bool	Auth(std::vector<std::string> message, Client &c, std::string Password){

	if (c.getIsSignedIn() == false) {
		if (CheckPASS(message, c, Password)){
			c.setIsSignedIn(true);
			return true;
		}
		return false;
	}
	else if (c.getIsSignedIn() == true) {
		if (c.isSettingsSetted() == false) {
			if (message[0] == "USER"){
				if (CheckUSER(message, c)) {
					std::cout << "username is: " << c.getUsername() << "\nfullname is: " << c.getFullName() << std::endl;
					return true;
				}
			}
			else if (message[0] == "NICK") {
				// CheckNICK(message, c);
			}
			else {
				std::cout << "Please enter a valid command" << std::endl;
				return false;
			}
		}
		else if (c.isSettingsSetted() == true){
			commands(message, c);
		}
	}

	// if (c.getCounter() == 0){
	// 	else{
	// 		c.incrementCounter();
	// 		c.setIsSignedIn(true);
	// 	}
	// }
	// else if (c.getCounter() == 1 && c.getIsSignedIn()){
	// 	if (!CheckUSER(message, c))
	// 		return false;
	// 	else
	// 		c.incrementCounter();
	// }
	// else if (c.getCounter() == 2 && c.getIsSignedIn()){
	// 	if (!CheckNICK(message, c)){
	// 		std::cout << "wsel hna!!" << std::endl;
	// 		return false;
	// 	}
	// 	else
	// 		c.incrementCounter();
	// }
	// std::string welcomeMessage = "User created succefully : " + c.getUsername() + "\n Your name is : " \
	// 		+ c.getFullName() + "\nAnd nickname is : " + c.getNickname() + "\n";
	// if (c.getCounter() == 3){
	// 	send(c.getClientId(),welcomeMessage.c_str(),welcomeMessage.length(),0);
	// 	c.incrementCounter();
	// }
	return true;
}
