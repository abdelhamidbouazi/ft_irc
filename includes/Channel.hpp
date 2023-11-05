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
		bool		invite_only;
		bool		isTopic;
		std::string	key;

	public:
		Channel(std::string name, std::map<std::string, Client&> owner);
		~Channel();
};

# endif
