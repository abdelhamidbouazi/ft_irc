#include "../includes/Client.hpp"
#include "../includes/Replies.hpp"

std::vector<std::string> Client::users;
std::map<std::string, int> Client::usersIds;
std::vector<std::string> Client::nicknames;

Client::Client() {}
Client::Client(int connection)
{
	isIn = false;
	mode = false;
	isSignedIn = false;
	settingsSetted = false;
	nickname = "";
	fullName = "";
	username = "";
	this->clientId = connection;
	UFlag = false;
	NFlag = false;
	channelCount = 0;
	startTime = std::time(nullptr);
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

bool Client::eraseNickname(Client &c)
{
	std::vector<std::string>::iterator it;
	it = std::find(nicknames.begin(), nicknames.end(), c.nickname);
	if (it != nicknames.end())
	{
		nicknames.erase(it);
		return true;
	}
	return false;
}
bool Client::eraseUser(Client &c)
{
	std::vector<std::string>::iterator it;
	it = std::find(users.begin(), users.end(), c.username);
	if (it != users.end())
	{
		users.erase(it);
		return true;
	}
	return false;
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

void Client::removeUserFromMap(std::string nickname)
{
    usersIds.erase(nickname);
}

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
	usersIds.insert(std::pair<std::string, int>(nickname, clientId));
}

void Client::setFullName(std::string fullName)
{
	this->fullName = fullName;
}

void Client::addUser(std::string username, Client &c)
{
	(void)c;
	if (username.length() == 0)
		return ;
	if (username.length() > 1)
	{
		this->username = username;
		users.push_back(username);
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

int Client::getChannelCount()
{
	return this->channelCount;
}

int Client::getIdByUsername(std::string username)
{
	std::map<std::string, int>::iterator it = usersIds.find(username);
	if (it != usersIds.end())
	{
		return it->second;
	}
	else
	{
		return -1;
	}
}

void Client::setChannelCount(int count)
{
	this->channelCount = count;
}

std::time_t Client::getStartTime() const
{
	return this->startTime;
}

std::string Client::getLocalhost() const
{
    return this->localhost;
}

void Client::setLocalhost(std::string localhost)
{
    this->localhost = localhost;
}
