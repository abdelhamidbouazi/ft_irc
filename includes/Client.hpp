# ifndef CLIENT_HPP
# define CLIENT_HPP


#include "Args.hpp"

class Client
{
	private:
		bool		isIn;
		bool		isSignedIn;
		std::string	nickname;
		std::string	fullName;
		int			clientId;
		int			counter;

	public:
		Client(int clientId);
		~Client();

		bool		getIsIn();
		bool		getIsSignedIn();
		std::string	getNickname();
		std::string	getFullName();
		int			getClientId();
		int			getCounter();

		void		setIsIn(bool	isIn);
		void		setIsSignedIn(bool	isSignedIn);
		void		setNickname(std::string	nickname);
		void		setFullName(std::string	fullName);
		void		setClientId(int	clientId);
		void		setCounter(int	counter);

};

bool	Auth(std::string message, Client &client, std::string Password);

# endif
