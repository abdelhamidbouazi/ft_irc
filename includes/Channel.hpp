# ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"

#include <map>

class Channel
{
	private:
		std::string channel;
		std::map<std::string, Client&>	users;
		std::map<std::string, Client&>	operators;
		int			limitUsers;
		bool		inviteOnly;
		bool		isTopic;
		std::string	key;
		static map <std::string, Channel &ch>	channelMap;

	public:
		Channel(std::string name, Client &owner);
		~Channel();

		std::string getChannel();
		std::map<std::string, Client&>	getUsers();
		std::map<std::string, Client&>	getOperators();
		int			getLimitUsers();
		bool		getInvite_only();
		bool		getIsTopic();
		std::string	getKey();

		void setChannel(std::string _channel);
		void setlimitUsers(int _limit);
		void setInviteOnly(bool _val);
		void setIsTopic(bool _val);
		void setKey(std::string _key);
		void addUsers(std::string username, Client &c);

		void setOperators(std::string, Client &c);
		void setUsers(std::string, Client &c);

};

# endif
