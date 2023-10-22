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

namespace HDE 
{
	class SocketHde 
	{
		private:
			int sock;
			int connection;
			struct sockaddr_in address;
			struct pollfd fds[200];
			int timeout;
			int rc;
			int on;
			int end_server;
			int nfds;
			std::string localhost;
		public:
			SocketHde(int domain, int service, int protocol, int port, unsigned long interface);
			virtual int connect_network( int sock, struct sockaddr_in address) = 0;
			void test_connection(int item_to_test);
			void test_connection_for_setsockopt(int item_to_test);
			void start_polling();
			struct sockaddr_in get_address();
			int get_sock();
			int get_connection();
			void set_connection(int connection);
			std::string ClientIp(int sock);
			std::string getHostAdresse();
	};
}


#endif
