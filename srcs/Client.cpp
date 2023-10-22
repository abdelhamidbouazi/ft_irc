#include "../includes/Client.hpp"

Client::Client(int clientId)
{
	isIn = false;
	isSignedIn = false;
	nickname = "";
	fullName = "";
	this->clientId = clientId;
	counter = 0;
}

Client::~Client()
{
}

bool Client::getIsIn()
{
	return isIn;
}

bool Client::getIsSignedIn()
{
	return isSignedIn;
}

std::string Client::getNickname()
{
	return nickname;
}

std::string Client::getFullName()
{
	return fullName;
}

int Client::getClientId()
{
	return clientId;
}

int Client::getCounter()
{
	return counter;
}


void Client::setIsIn(bool isIn)
{
	this->isIn = isIn;
}

void Client::setIsSignedIn(bool isSignedIn)
{
	this->isSignedIn = isSignedIn;
}

void Client::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void Client::setFullName(std::string fullName)
{
	this->fullName = fullName;
}

void Client::setClientId(int clientId)
{
	this->clientId = clientId;
}

void Client::setCounter(int counter)
{
	this->counter = counter;
}
