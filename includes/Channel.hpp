# ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"

#include <map>

class Channel
{
	private:
		std::string channel;
		static std::vector<Client>	users;
		static std::vector<Client>	operators;
		int			limitUsers;
		bool		inviteOnly;
		bool		isTopic;
		std::string	key;
		static std::map<std::string, Channel&> channelsMap;
		// static std::vector<std::string, std::string> messages;

	public:
		Channel(std::string name, Client owner);
		~Channel();

		std::string getChannelName();
		std::vector<Client>	getUsers();
		std::vector<Client>	getOperators();
		int			getLimitUsers();
		bool		getInvite_only();
		bool		getIsTopic();
		std::string	getKey();
		// Channel& getChannel(std::string channelName);
		// static std::map<std::string, Channel&> &getChannelsMap();
		static Channel& getChannel(const std::string& channelName);

		void setChannel(std::string _channel);
		void setlimitUsers(int _limit);
		void setInviteOnly(bool _val);
		void setIsTopic(bool _val);
		void setKey(std::string _key);

		void addUsers(Client c);
		void addOperators(Client c);

		void addChannels(std::string channelName, Channel &ch);
};

# endif
