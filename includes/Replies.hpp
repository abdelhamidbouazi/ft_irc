# ifndef REPLIES_HPP
# define REPLIES_HPP

#include "Client.hpp"

class Replies
{
	public:
		Replies(/* args */);
		~Replies();

		static void NOTENOUGHPARAMS(Client c);
		static void WRONGPASSWORD(Client c);
		static void ERR_EMPTYNICKNAME (Client c);
		static void ERR_ALREADYREGISTRED(Client c);
		static void ERR_NICKNAMEINUSE(Client c);
		static void ERR_INVALIDNICKNAME(Client c);
};

#define ERR_NEEDMOREPARAMS(cmd, nick)    "461 " + nick + " " + cmd + " :Not enough parameters\r\n"

# endif
