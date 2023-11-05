#include "../includes/Channel.hpp"

#include <iostream>
#include <vector>

Channel::Channel(std::string name, Client &owner)
		: channel(name),
			limitUsers(-1),
			inviteOnly(false),
			isTopic(false),
			key("")
{
	// operators.insert(std::make_pair <std::string, Client&> (owner.getUsername(), &owner));
}


Channel::~Channel()
{}

std::string Channel::getChannel()
{
	return channel;
}

std::map<std::string, Client &> Channel::getUsers()
{
	return std::map<std::string, Client &>();
}

std::map<std::string, Client &> Channel::getOperators()
{
	return std::map<std::string, Client &>();
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

void Channel::addUsers(std::string username, Client &c)
{
	// add user
}
void Channel::setOperators(std::string, Client &c)
{
}

void Channel::setUsers(std::string, Client &c)
{
}
