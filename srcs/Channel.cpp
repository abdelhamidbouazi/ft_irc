#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include <iostream>
#include <vector>


Channel::Channel(std::string name, Client owner, std::string key)
{
	channel = name;
	limitUsers = -1;
	inviteOnly = false;
	isTopic = false;
	this->key = key;
	users.push_back(owner);
	operators.push_back(owner);
}

Channel::Channel(std::string name)
{

}

Channel::~Channel()
{}

void Channel::addUsers(Client c)
{
	users.push_back(c);
}
void Channel::addOperators(Client c)
{
	for (std::vector<Client>::iterator it = users.begin(); it < users.end(); ++it) {
		if (it->getUsername() == c.getUsername()) {
			operators.push_back(c);
			return ;
		}
	}
	std::cout << c.getUsername() << " is not a user in the channel invite user first!" << std::endl;
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

Client& Channel::getUserByName(std::string username) {
    for (std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it) {
        if (it->getUsername() == username) {
            return *it;
        }
    }
    std::cout << "User not found" << std::endl;
    static Client invalidUser(-1); // Create a special "invalid" user
    return invalidUser; // Return a reference to the "invalid" user
}

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
