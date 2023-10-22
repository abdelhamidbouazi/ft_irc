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
};


# endif
