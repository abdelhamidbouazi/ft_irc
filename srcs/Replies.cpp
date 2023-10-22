#include "../includes/Replies.hpp"
#include "../includes/Replies.hpp"

std::string getHostName(){
 	char hostname[256]; // Assuming the hostname won't be longer than 255 characters

    if (gethostname(hostname, sizeof(hostname)) == 0) {
		return hostname;
    } else {
        std::cerr << "Error getting hostname." << std::endl;
    }
	return NULL;
}

Replies::Replies()
{
}

void Replies::NOTENOUGHPARAMS(Client c)
{
	std::string message =  ":" + getHostName() + " 461 " +  c.getNickname() + " :Not enough parameters" + "\r\n";
    send(c.getClientId(),message.c_str(),message.length(),0);
}

void Replies::WRONGPASSWORD(Client c)
{
    std::string message =   ":" + getHostName() + " 464 " + c.getNickname() + " :" + "Password incorrect" + "\r\n";
    send(c.getClientId(),message.c_str(),message.length(),0);
}
