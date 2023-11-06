#include "../includes/Channel.hpp"
#include "../includes/Client.hpp"
#include <iostream>
#include <vector>

Channel::Channel(std::string name, Client owner)
{
	channel = name;
	limitUsers = -1;
	inviteOnly = false;
	isTopic = false;
	key = "";
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
	operators.push_back(c);
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
