#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Args.hpp"

#include <vector>

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
		// int counter;
		// Declare the static vector of strings as a private static member
		static std::vector<std::string> users;
		static std::vector<std::string> nicknames;


	public:
		Client(int clientId);
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
		std::vector<std::string> getUsers();
		std::vector<std::string> getNicknames();
		std::vector<std::string> getAllUsers();
		int getClientId();
		// int getCounter();


		void setIsIn(bool isIn);
		void setMode(bool mode);
		void setIsSignedIn(bool isSignedIn);
		void setIsSettingsSetted(bool settingsSetted);
		void setNickname(std::string nickname);
		void setFullName(std::string fullName);
		void addUser(std::string username, Client &c);
		void setClientId(int clientId);
		// void incrementCounter();
};

// Define the static vector of strings outside the class definition


bool	Auth(std::vector<std::string> message, Client &c, std::string Password);

#endif
