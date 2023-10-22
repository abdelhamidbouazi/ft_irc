#include "../includes/Client.hpp"
#include "../includes/Args.hpp"
#include <vector>
#include "../includes/Replies.hpp"

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
	return 0;
}
int CheckUSER(std::string message){
	return 0;
}
int CheckNICK(std::string message){
	return 0;
}

bool	Auth(std::string message, Client &c, std::string Password){

	if (c.getCounter() == 0){
		if (!CheckPASS(message, c, Password)){
			return false;
		}
		else{
			c.setCounter(c.getCounter() + 1);
			c.setIsSignedIn(true);
		}
	}
	else if (c.getCounter() == 1 && c.getIsSignedIn()){
		std::cout << "Reh Wsell\n";
		CheckUSER(message);

	}
	else if (c.getCounter() == 1 && c.getIsSignedIn())
		CheckNICK(message);
	return true;
}
