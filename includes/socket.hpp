#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>

namespace HDE 
{
	class SocketHde 
	{
		private:
			int sock;
			int connection;
			struct sockaddr_in address;
		public:
			SocketHde(int domain, int service, int protocol, int port, unsigned long interface);
			virtual int connect_network( int sock, struct sockaddr_in address) = 0;
			void test_connection(int item_to_test);
			struct sockaddr_in get_address();
			int get_sock();
			int get_connection();
			void set_connection(int connection);
	};
}


#endif
