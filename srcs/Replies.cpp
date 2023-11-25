#include "../includes/Replies.hpp"

Replies::Replies()
{
}

Replies::~Replies()
{
}

std::string getHostName()
{
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0)
        return hostname;
    else
        std::cerr << "Error getting hostname." << std::endl;
    return NULL;
}

void Replies::WRONGPASSWORD(Client c)
{
    std::string message = ":" + getHostName() + " 464 " + c.getNickname() + " :" + "Password incorrect" + "\r\n";
    send(c.getClientId(), message.c_str(), message.length(), 0);
}

void Replies::ERR_EMPTYNICKNAME(Client c)
{
    std::string message = ":" + getHostName() + " 431 " + c.getNickname() + " :" + "No nickname given" + "\r\n";
    send(c.getClientId(), message.c_str(), message.length(), 0);
}

void Replies::ERR_INVALIDNICKNAME (Client c)
{
    std::string message =   ":" + getHostName() + " 432 " + c.getNickname() + " :" + "Erroneus nickname" + "\r\n";
    send(c.getClientId(),message.c_str(),message.length(),0);
}
