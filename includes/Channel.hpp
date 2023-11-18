# ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"
#include <map>
#include <vector>


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
		~Channel();

		//getters
		std::string getChannelName();
		std::vector<Client>	getUsers();
		std::vector<Client>	getOperators();
		std::vector<std::string> getInvitedUser();
		std::string getOwner();
		std::string	getKey();
		std::string getTopic();
		int			getLimitUsers();
		bool		getInvite_only();
		bool		getIsTopic();
		bool		getHasOwner();

		//setters
		void setChannel(std::string _channel);
		void setHasOwner(bool hasOwner);
		void setlimitUsers(int _limit);
		void setInviteOnly(bool _val);
		void setIsTopic(bool _val);
		void setKey(std::string _key);
		bool eraseOperator(Client c);
		bool eraseUser(Client c);
		bool eraseInvitedUser(std::string name);
		void setOwner(std::string name);
		void setTopic(std::string topic);

		void addUsers(Client c);
		bool addOperators(Client c);
		void addInvited(Client c);
		bool addInvitedUser(std::string name);
};

# endif
