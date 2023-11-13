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

#define ERR_NEEDMOREPARAMS(cmd, nick)    " 461 " + nick + " " + cmd + " :Not enough parameters\r\n"
#define ERR_BADCHANMASK(param, nick) " 476 " + nick + " " + param + " :Bad Channel Mask\r\n" 
#define ERR_TOOMANYCHANNELS(param, nick) " 405 " + nick + " " + param + " :You have joined too many channels\r\n" 
#define ERR_CHANNELISFULL(param, nick) " 471 " + nick + " " + param + " :Cannot join channel (+l)\r\n" 
#define ERR_BADCHANNELKEY(param, nick) " 475 " + nick + " " + param + " :Cannot join channel (+k)\r\n" 
#define ERR_INVITEONLYCHAN(param, nick) " 473 " + nick + " " + param + " :Cannot join channel (+i)\r\n"
#define ERR_NOSUCHCHANNEL(param, nick) " 403 " + nick + " " + param + " :No such channel\r\n" 
#define ERR_NOTONCHANNEL(param) " 442 " + param + " :You're not on that channel\r\n"
#define ERR_NOCHANMODES(param, nick) " 477 " + nick + " " + param + " :Channel doesn't support modes\r\n"
#define ERR_CHANOPRIVSNEEDED(param, nick) " 482 " + nick + " " + param + " :You're not channel operator\r\n"
#define RPL_TOPIC(nick, param, topic) " 332 " + nick + " " + param + " :" + topic + "\r\n"
#define RPL_NOTOPIC(nick, param) " 331 " + nick + " " + param + " :No topic is set\r\n"
#define ERR_NORECIPIENT(param) " 411 :No recipient given " + param + "\r\n"
#define ERR_NOTEXTTOSEND " 412 :No text to send\r\n"
#define ERR_TOOMANYTARGETS(param) " 407 " + param + " :recipients. No message delivered\r\n"


# endif
