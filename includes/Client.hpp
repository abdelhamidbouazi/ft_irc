#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Args.hpp"

#include <vector>
#include <map>
#include "Channel.hpp"
#include <ctime>


#define USER_MAX_CHANNEL 30

class Channel;
class Client
{
	private:
		bool isIn;
		bool isSignedIn;
		bool settingsSetted;
		bool mode;
		std::string nickname;
		std::string fullName;
		std::string username;
		int clientId;
		int clientFd;
		std::time_t startTime;
		// int counter;
		// Declare the static vector of strings as a private static member
		static std::vector<std::string> users;
		// static std::vector<std::string> operators;
		static std::vector<std::string> nicknames;
		static std::map<std::string, int> usersIds;
		bool	UFlag;
		bool	NFlag;
		int channelCount;

	public:
		Client();
		Client(int clientId);
		// Client(int clientId, std::string nickname);
		~Client();

		// i add this
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
		// int getCounter();


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
		// void incrementCounter();
		void setUFlag();
		void setNFlag();

		static bool CheckUser(std::vector<std::string> message, int place);
};

// Define the static vector of strings outside the class definition


bool	Auth(std::vector<std::string> message, Client &c, std::string Password, std::map<std::string, Channel&> channelsMap, std::vector<std::pair<std::string , std::string > > joinVector);
#endif
