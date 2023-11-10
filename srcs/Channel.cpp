#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include <iostream>
#include <vector>

Channel::Channel(){}
Channel::Channel(std::string name, Client owner, std::string key)
{
	channel = name;
	limitUsers = -1;
	inviteOnly = false;
	isTopic = false;
	hasOwner = true;
	this->key = key;
	this->owner = owner.getNickname();
	users.push_back(owner);
	operators.push_back(owner);
}

Channel::Channel(std::string name)
{

}

Channel::~Channel()
{}

void Channel::addInvitedUser(std::string name)
{
	this->invitedUser.push_back(name);
}
void Channel::eraseInvitedUser(std::string name)
{
	std::vector<std::string>::iterator it = find(invitedUser.begin(), invitedUser.end(), name);
	if(it == invitedUser.end())
		return ;
	invitedUser.erase(it);
}
std::string Channel::getOwner()
{
	return this->owner;
}

bool Channel::getHasOwner()
{
	return hasOwner;
}

void Channel::setHasOwner(bool hasOwner)
{
	this->hasOwner = hasOwner;
}

void Channel::addUsers(Client c)
{
	users.push_back(c);
}

void Channel::addOperators(Client c)
{
	std::cout << "client name : "<<c.getNickname() << "id is :"<< c.getClientId() <<std::endl;
	std::vector<Client>::iterator it;
	for(it = users.begin() ; it != users.end() ; ++it)
	{
		if(it->getUsername() == c.getUsername())
			operators.push_back(c);
			return ;
	}
	if(it == users.end())
	{
		std::cout << c.getUsername() << " is not a user in the channel invite user first!" << std::endl;
	}
	// std::cout << "**entred to the add opereator 2" << std::endl;
	// for (std::vector<Client>::iterator it = users.begin(); it < users.end(); it++) {
	// 	if (it->getUsername() == c.getUsername()) {
	// 		operators.push_back(c);

	// 	}
	// 	std::cout << it->getClientId() << " " << it->getNickname() << std::endl;
	// 	std::cout << "after the if" << std::endl;
	// }
}

void Channel::eraseOperator(Client c)
{
    for (std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it)
    {
        if (it->getClientId() == c.getClientId())
        {
            operators.erase(it);
            break;
        }
    }
}

std::string Channel::getChannelName()
{
	return channel;
}

std::vector<Client> Channel::getUsers()
{
	return users;
}
std::vector<Client> Channel::getOperators()
{
	return operators;
}

std::vector<std::string> Channel::getInvitedUser()
{
    return this->invitedUser;
}
int Channel::getLimitUsers()
{
	return limitUsers;
}

bool Channel::getInvite_only()
{
	return inviteOnly;
}

bool Channel::getIsTopic()
{
	return isTopic;
}

std::string Channel::getKey()
{
	return this->key;
}

// Client& Channel::getUserByName(std::string username) {
//     for (std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it) {
//         if (it->getUsername() == username) {
//             return *it;
//         }
//     }
//     std::cout << "User not found" << std::endl;
//     Client invalidUser(-1); // Create a special "invalid" user
//     return invalidUser; // Return a reference to the "invalid" user
// }

void Channel::setChannel(std::string _channel)
{
	this->channel = _channel;
}

void Channel::setlimitUsers(int _limit)
{
	this->limitUsers = _limit;
}

void Channel::setInviteOnly(bool _val)
{
	this->inviteOnly = _val;
}

void Channel::setIsTopic(bool _val)
{
	this->isTopic = _val;
}

void Channel::setKey(std::string _key)
{
	this->key = _key;
}
