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
		int			limitUsers;
		bool		inviteOnly;
		bool		isTopic;
		std::string	key;
		
	public:
		Channel();
		Channel(std::string channel, Client owner, std::string key);
		Channel(std::string name);
		~Channel();

		std::string getChannelName();
		std::vector<Client>	getUsers();
		std::vector<Client>	getOperators();
		int			getLimitUsers();
		bool		getInvite_only();
		bool		getIsTopic();
		std::string	getKey();
		// Client& getUserByName(std::string username);

		void setChannel(std::string _channel);
		void setlimitUsers(int _limit);
		void setInviteOnly(bool _val);
		void setIsTopic(bool _val);
		void setKey(std::string _key);
		void eraseOperator(Client c);


		void addUsers(Client c);
		void addOperators(Client c);


};

# endif
