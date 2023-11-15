#include "../includes/Replies.hpp"

std::string getHostName()
{
    char hostname[256]; // Assuming the hostname won't be longer than 255 characters

    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        return hostname;
    }
    else
    {
        std::cerr << "Error getting hostname." << std::endl;
    }
    return NULL;
}

Replies::Replies()
{
}

Replies::~Replies()
{
}
void Replies::NOTENOUGHPARAMS(Client c)
{
    std::string message = ":" + getHostName() + " 461 " + c.getNickname() + " :Not enough parameters" + "\r\n";
    send(c.getClientId(), message.c_str(), message.length(), 0);
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

// void Replies::ERR_NICKNAMEINUSE (Client c)
// {
//     std::string message =   ":" + getHostName() + " 433 " + c.getNickname() + " :" + "Nickname is already in use" + "\r\n";
//     send(c.getClientId(),message.c_str(),message.length(),0);
// }

// void Replies::ERR_ALREADYREGISTRED(Client c)
// {
//     std::string message = ":" + getHostName() + " 462 " + c.getNickname() + " :" + "You are registred" + "\r\n";
//     send(c.getClientId(), message.c_str(), message.length(), 0);
// }

// void Replies::ERR_NICKCOLLISION (Client c)
// {

//     std::string message =   ":" + getMachineHostName() + " 436 " + c.get_nickname() + " :" + "Nickname collision KILL from" + "\r\n";
//     send(c.get_fd(),message.c_str(),message.length(),0);
// }
