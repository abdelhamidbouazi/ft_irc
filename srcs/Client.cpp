#include "../includes/Client.hpp"
#include "../includes/Replies.hpp"

std::vector<std::string> Client::users;
std::vector<std::string> Client::nicknames;


Client::Client(int clientId)
{
	isIn = false;
	mode = false;
	isSignedIn = false;
	settingsSetted = false;
	nickname = "";
	fullName = "";
	username = "";
	this->clientId = clientId;
	// counter = 0;
}

Client::~Client()
{
}

bool Client::getIsIn()
{
	return isIn;
}
bool Client::getMode()
{
	return mode;
}

bool Client::getIsSignedIn()
{
	return isSignedIn;
}
bool Client::isSettingsSetted()
{
	return this->settingsSetted;
}

std::string Client::getNickname()
{
	return nickname;
}

std::string Client::getUsername()
{
	return this->username;
}
std::string Client::getFullName()
{
	return fullName;
}

std::vector<std::string> Client::getUsers()
{
	return this->users;
}

std::vector<std::string> Client::getNicknames()
{
	return this->nicknames;
}

std::vector<std::string> Client::getAllUsers()
{
	for (size_t i = 0; i < users.size(); i++){
		std::cout << users[i] << " " << std::endl;
	}
	return this->users;
}

int Client::getClientId()
{
	return clientId;
}

// int Client::getCounter()
// {
// 	return counter;
// }

void Client::setIsIn(bool isIn)
{
	this->isIn = isIn;
}
void Client::setMode(bool mode)
{
	this->mode = mode;
}

void Client::setIsSignedIn(bool isSignedIn)
{
	this->isSignedIn = isSignedIn;
}
void Client::setIsSettingsSetted(bool settingsSetted)
{
	this->isSignedIn = settingsSetted;
}

void Client::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void Client::setFullName(std::string fullName)
{
	this->fullName = fullName;
}

void Client::addUser(std::string username, Client &c)
{
	if (username.length() == 0)
		Replies::ERR_ALREADYREGISTRED(c);
	if (username.length() > 2) {
		this->username = username;
		users.push_back(username);
	}
	else {
		std::cout << "Username is less than 2\n";
	}
}
void Client::setClientId(int clientId)
{
	this->clientId = clientId;
}

// void Client::incrementCounter()
// {
// 	this->counter++;
// }
