#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Args.hpp"
#include "Channel.hpp"
#include "socket.hpp"
#include <map>

#define USER_MAX_CHANNEL 30

class Channel;
class Client
{
	private:
		bool	isIn;
		bool	isSignedIn;
		bool	settingsSetted;
		bool	mode;
		bool	UFlag;
		bool	NFlag;
		int	channelCount;
		int	clientId;
		int	clientFd;
		std::string	nickname;
		std::string	fullName;
		std::string	username;
		std::string	localhost;
		std::time_t	startTime;
		static	std::vector<std::string> users;
		static	std::vector<std::string> nicknames;
		static	std::map<std::string, int> usersIds;
	public:
		Client();
		Client(int connection);
		~Client();

		std::string commande_str;
		bool getIsIn();
		bool getMode();
		bool getIsSignedIn();
		bool isSettingsSetted();
		std::string getNickname();
		std::string getUsername();
		std::string getFullName();
		static std::vector<std::string> getUsers();
		std::vector<std::string> getNicknames();
		std::vector<std::string> getAllUsers();
		int getClientId();
		int getClientFd();
		bool getUFlag();
		bool getNFlag();
		int getChannelCount();
		static int getIdByUsername(std::string username);
		std::time_t getStartTime() const;
		std::string getLocalhost() const;
		// int getCounter();
		void removeUserFromMap(std::string nickname);
		void setIsIn(bool isIn);
		void setMode(bool mode);
		void setIsSignedIn(bool isSignedIn);
		void setIsSettingsSetted(bool settingsSetted);
		void setNickname(std::string nickname);
		void setFullName(std::string fullName);
		void addUser(std::string username, Client &c);
		void setClientId(int clientId);
		void setClientFd(int clientFd);
		void setChannelCount(int count);
		bool eraseNickname(Client &c);
		bool eraseUser(Client &c);
		void setLocalhost(std::string localhost);
		// void incrementCounter();
		void setUFlag();
		void setNFlag();

		static bool CheckUser(std::vector<std::string> message, int place);
};

// Define the static vector of strings outside the class definition


bool	Auth(std::vector<std::string> message, Client &c, std::string Password, std::map<std::string, Channel&> channelsMap, std::vector<std::pair<std::string , std::string > > joinVector);
#endif
