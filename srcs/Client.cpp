#include "../includes/Client.hpp"
#include "../includes/Replies.hpp"

std::vector<std::string> Client::users;
std::map<std::string, int> Client::usersIds;
std::vector<std::string> Client::nicknames;

Client::Client(){}
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
	UFlag = false;
	NFlag = false;
	// usersIds.insert(std::pair<std::string, int>("", 0));
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
bool Client::getUFlag()
{
	return UFlag;
}
bool Client::getNFlag()
{
	return NFlag;
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
	return users;
}

std::vector<std::string> Client::getNicknames()
{
	return this->nicknames;
}

std::vector<std::string> Client::getAllUsers()
{
	for (size_t i = 0; i < users.size(); i++)
	{
		std::cout << users[i] << " " << std::endl;
	}
	return this->users;
}

int Client::getClientId()
{
	return clientId;
}
int Client::getClientFd()
{
	return clientFd;
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
	this->settingsSetted = settingsSetted;
}

void Client::setNickname(std::string nickname)
{
	this->nicknames.push_back(nickname);
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
	if (username.length() > 1)
	{
		this->username = username;
		users.push_back(username);
		usersIds.insert(std::pair<std::string, int>(username, clientId)); // Add username and id to the map
		// std::cout << "Username from the map id is : " << usersIds.at(username) << std::endl;
	}
	else
	{
		std::cout << "Username is less than 2\n";
	}
}
void Client::setClientId(int clientId)
{
	this->clientId = clientId;
}
void Client::setClientFd(int clientFd)
{
	this->clientFd = clientFd;
}

void Client::setUFlag()
{
	this->UFlag = true;
}
void Client::setNFlag()
{
	this->NFlag = true;
}

// void Client::incrementCounter()
// {
// 	this->counter++;
// }

int Client::getChannelCount()
{
	return this->channelCount;
}

int Client::getIdByUsername(std::string username)
{

    // for(std::map<std::string, int>::iterator it = usersIds.begin(); it != usersIds.end() ; it++)
	// 	std::cout << "client name is : " << it->first << " client id is : " << it->second << std::endl;
    std::map<std::string, int>::iterator it = usersIds.find(username);
    if (it != usersIds.end())
    {
		// std::cout << "function getIdByUsername: return : " << it->second<< std::endl;
        // The username was found. Return the associated id.
        return it->second;
    }
    else
    {
		std::cout << "User not found!!!" << std::endl;
        // The username was not found. Return a sentinel value to indicate this.
        // -1 is often used for this purpose, but you should choose a value that makes sense for your application.
        return -1;
    }
}

// Client& getUserById(int id) {
//     std::map<int, Client&>::iterator it = users.find(id);
//     if (it != users.end()) {
//         return it->second;
//     } else {
//         throw std::runtime_error("User not found");
//     }
// }

void Client::setChannelCount(int count)
{
	this->channelCount = count;
}
