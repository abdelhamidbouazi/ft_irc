#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <map>
#include <algorithm>
#include <arpa/inet.h>
#include <sstream>
#include <netdb.h>
#include <fcntl.h>
#include <chrono>
#include <vector>

#include "../includes/Commande.hpp"
#include "../includes/Client.hpp"
#include "../includes/Channel.hpp"
#include "../includes/socket.hpp"

#define MAX_TARGET 1


namespace HDE
{
	class SocketHde
	{
		private:
			int sock;
			int connection;
			struct sockaddr_in address;
			// struct pollfd fds[200];
			// struct pollfd fds[200];
			std::vector<pollfd> fds;
			int timeout;
			int rc;
			int on;
			int end_server;
			int port;
			std::string password;
			std::map<std::string, int> AllUsers;
			int flagQuit ;
		public:
			std::map<int, Client> clt;
			std::map<std::string, Channel*> channelsMap;
			SocketHde(int domain, int service, int protocol, int port, unsigned long interface, std::string password);
			virtual int connect_network( int sock, struct sockaddr_in address) = 0;
			void test_connection(int item_to_test);
			void test_connection_for_setsockopt(int item_to_test);
			void start_polling();

			struct sockaddr_in get_address();
			int get_sock();
			int get_connection();
			std::string getHostAdresse();
			int getPort();
			std::string getPassword();

			void setPort(int port);
			void setPassword(std::string password);
			void set_connection(int connection);

			std::string ClientIp(int sock);

			// commands
			void	Auth(std::vector<std::string> message, std::vector<std::pair<std::string , std::string > > joinVector,int i);
			void	commands(std::vector<std::string> message, std::vector<std::pair<std::string , std::string > > joinVector,int i);
			void	Join(std::vector<std::pair<std::string , std::string > > joinVector,int i);
			void	CheckMODE(std::vector<std::string> message, int i);
			void	Part(std::vector<std::string> message, int i);
			void	Topic(std::vector<std::string> message, int i);
			void	Privmsg(std::vector<std::string> message, int i);
			void	Bot(int i);
			bool	CheckKICK(std::vector<std::string> message, int i);
			void	CheckINVITE(std::vector<std::string> message, int i);
			void	CheckQUIT(int i);

			// mode tools
			void	modeT(std::vector<std::string> message, int mode, int i);
			void	modeI(std::vector<std::string> message, int mode, int i);
			void	modeK(std::vector<std::string> message,int mode, int i);
			void	modeO(std::vector<std::string> message,int mode, int user, int i);
			void	modeL(std::vector<std::string> message,int mode, int i);
			bool	checkUserInChannelOperator(Channel *chan, std::string name);
			bool	checkUserInChannel(Channel *chan, std::string name);

			//auth
			int		CheckPASS(std::vector<std::string> message, Client &c, std::string Pass, int i);
			int		CheckUSER(std::vector<std::string> message, Client &c, int i);
			int 	CheckNICK(std::vector<std::string> message, Client &c, int i);
			bool	isFound(const std::vector<std::string> &vec, const std::string &str);
			//tools
			void	sendMessageToAll(int i, std::string channelname);
			void	sendMessageToAllForPart(int i, std::string channelname);
			void	sendMessageToAllForTopic(int i, std::string channelname, int flag);
			void	sendMessageToAllForPrivmsg(int i, std::string channelname, std::string message);
			void	sendMessage(std::string message, int fd);

			// checkers
			bool	CheckChannelsMap(std::vector<std::string> message, int place);

			void	CleanQuit(std::string nickname, int i);
			void	sendMessageToAllForQuit(int i, std::string channelname);
			void	sendMessageToAllForInvite(int i, std::string channelname, std::string message);
	};
}

#endif
