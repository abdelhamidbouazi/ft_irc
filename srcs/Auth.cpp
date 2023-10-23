#include "../includes/Client.hpp"
#include "../includes/Args.hpp"
#include <vector>
#include "../includes/Replies.hpp"
#include <algorithm>

void splitString(const std::string& input, std::vector<std::string>& tokens) {
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
}

std::string clearSpaces(std::string line)
{
    std::string ws = " \n\r\t\f\v";
    size_t start = line.find_first_not_of(ws);
    size_t end = line.find_last_not_of(ws) + 1;
    size_t len = end - start;
    if(end != 0)
        line = line.substr(start,len);
    return line;
}

int CheckPASS(std::string message, Client	&c, std::string Pass){
	std::vector<std::string> newMessage;
	splitString(message, newMessage);

	newMessage[1] = clearSpaces(newMessage[1]);
	if (newMessage.size() != 2)
	{
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	if (newMessage[0] == "PASS"){
		if (Pass != newMessage[1]){
			Replies::WRONGPASSWORD(c);
			return 0;
		}
		return 1;
	}
	else{
		std::cout << "Enter Password First\n";
		return 0;
	}
}

int CheckUSER(std::string message, Client &c){
	std::vector<std::string> newM;
	splitString(message, newM);
	std::vector<std::string>::iterator  it;

	it = find(newM.begin(), newM.end(), newM[1]);
	newM[1] = clearSpaces(newM[1]);
	if (newM.size() != 6)
	{
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	if (newM[0] == "USER" && newM[2] == "0" && newM[3] == "*")
	{
		if (it == newM.end()){
			Replies::ERR_ALREADYREGISTRED(c);
		}
		else{
			c.addUser(newM[1], c);
			c.setFullName(newM[4] + " " + newM[5]);
			return 1;
		}
	}

	return 0;
}

int CheckNICK(std::string message, Client &c){
	std::vector<std::string> newM;
	splitString(message, newM);
	std::vector<std::string>::iterator  it;

	it = find(newM.begin(), newM.end(), newM[1]);
	newM[1] = clearSpaces(newM[1]);
	if (newM.size() != 2)
	{
		Replies::NOTENOUGHPARAMS(c);
		return 0;
	}
	if(newM[0] == "NICK" && !newM[1].empty()){
		if (it == newM.end()){
			Replies::ERR_ALREADYREGISTRED(c);
		}
		else if (isdigit(newM[1][0]))
		{
			Replies::ERR_ALREADYREGISTRED(c);
		}
		else {
			c.setNickname(newM[1]);
			return 1;
		}
	}

	return 0;
}

bool	Auth(std::string message, Client &c, std::string Password){

	if (c.getCounter() == 0){
		if (!CheckPASS(message, c, Password)){
			return false;
		}
		else{
			c.incrementCounter();
			c.setIsSignedIn(true);
		}
	}
	else if (c.getCounter() == 1 && c.getIsSignedIn()){
		if (!CheckUSER(message, c))
			return false;
		else
			c.incrementCounter();
	}
	else if (c.getCounter() == 2 && c.getIsSignedIn()){
		if (!CheckNICK(message, c)){
			std::cout << "wsel hna!!" << std::endl;
			return false;
		}
		else
			c.incrementCounter();
	}
	std::string welcomeMessage = "User created succefully : " + c.getUsername() + "\n Your name is : " \
			+ c.getFullName() + "\nAnd nickname is : " + c.getNickname() + "\n";
	if (c.getCounter() == 3){
		send(c.getClientId(),welcomeMessage.c_str(),welcomeMessage.length(),0);
		c.incrementCounter();
	}
	return true;
}
