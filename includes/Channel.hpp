# ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"

#include <map>

class Client;

class Channel
{
	private:
		std::string channel;
		std::vector<Client>	users;
		std::vector<Client>	operators;
		std::vector<std::string> invitedUser;
		int			limitUsers;
		bool		inviteOnly;
		bool		isTopic;
		bool		hasOwner;
		std::string owner;
		std::string	key;
		std::string topic;

		
	public:
		Channel();
		Channel(std::string channel, Client owner, std::string key);
		Channel(std::string name);
		~Channel();

		std::string getChannelName();
		std::vector<Client>	getUsers();
		std::vector<Client>	getOperators();
		std::vector<std::string> getInvitedUser();
		int			getLimitUsers();
		bool		getInvite_only();
		bool		getIsTopic();
		bool		getHasOwner();
		std::string getOwner();
		std::string	getKey();
		std::string getTopic();
		// Client& getUserByName(std::string username);

		void setChannel(std::string _channel);
		void setHasOwner(bool hasOwner);
		void setlimitUsers(int _limit);
		void setInviteOnly(bool _val);
		void setIsTopic(bool _val);
		void setKey(std::string _key);
		void eraseOperator(Client c);
		void eraseUser(Client c);
		void eraseInvitedUser(std::string name);
		void setOwner(std::string name);
		void setTopic(std::string topic);


		void addUsers(Client c);
		void addOperators(Client c);
		void addInvitedUser(std::string name);


};

# endif
