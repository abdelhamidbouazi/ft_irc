#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include "../includes/Replies.hpp"

#include <iostream>
#include <vector>

Channel::Channel() {}
Channel::Channel(std::string name, Client owner, std::string key)
{
	channel = name;
	limitUsers = 3;
	inviteOnly = false;
	isTopic = true;
	hasOwner = true;
	this->key = key;
	this->owner = owner.getNickname();
	users.push_back(owner);
	operators.push_back(owner);
}

Channel::~Channel()
{
}

bool Channel::addInvitedUser(std::string name)
{
	this->invitedUser.push_back(name);
	return true;
}
bool Channel::eraseInvitedUser(std::string name)
{
	std::vector<std::string>::iterator it = find(invitedUser.begin(), invitedUser.end(), name);
	if (it == invitedUser.end()) {
		return false;
	}
	invitedUser.erase(it);
	return true;
}
std::string Channel::getOwner()
{
	return this->owner;
}
void Channel::setOwner(std::string name)
{
	this->owner = name;
}

bool Channel::getHasOwner()
{
	return hasOwner;
}

void Channel::setHasOwner(bool hasOwner)
{
	this->hasOwner = hasOwner;
}

std::string Channel::getTopic()
{
	return this->topic;
}

void Channel::setTopic(std::string topic)
{
	this->topic = topic;
}

void Channel::addUsers(Client c)
{
	users.push_back(c);
}
void Channel::addInvited(Client c)
{
	invitedUser.push_back(c.getNickname());
}

bool Channel::addOperators(Client c)
{
    // Check if client is already an operator
    for (std::vector<Client>::iterator op = operators.begin(); op != operators.end(); ++op) {
        if (op->getUsername() == c.getUsername()) {
            return false;
        }
    }

    std::vector<Client>::iterator it;
    for (it = users.begin(); it != users.end(); ++it)
    {
        if (it->getUsername() == c.getUsername()) {
            operators.push_back(c);
            return true;
        }
    }
    if (it == users.end())
    {
        return false;
    }
    return false;
}

bool Channel::eraseOperator(Client c)
{
	for (std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it)
	{
		if (it->getClientId() == c.getClientId())
		{
			operators.erase(it);
			return true;
		}
	}
	return false;
}

bool Channel::eraseUser(Client c)
{
	for (std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it->getClientId() == c.getClientId())
		{
			users.erase(it);
			return true;
		}
	}
	return false;
}

bool Channel::eraseUser(std::string nickname)
{
	for (std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it->getNickname() == nickname)
		{
			users.erase(it);
			return true;
		}
	}
	return false;
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
