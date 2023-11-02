/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharrach <sharrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:09:18 by sharrach          #+#    #+#             */
/*   Updated: 2023/09/17 14:39:30 by sharrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::Initval(){
	on = 1;
	listen_sd = -1;
	new_sd = -1;
	end_server = 0;
	compress_array = 0;
	nfds = 1,
	current_size = 0;
}


void Server::CreateServ(){
	listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sd < 0) {
		perror("socket() failed");
		exit(-1);
	}

	rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if (rc < 0) {
		perror("setsockopt() failed");
		close(listen_sd);
		exit(-1);
	}

	if (fcntl(listen_sd, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl(F_SETFL) failed");
		close(listen_sd);
		exit(-1);
	}
}


Server::Server(int serverport, std::string password) {

	if(PasswordCheck(password) == 0)
		exit (-1);
	this->password = password;
	this->serverport = serverport;
	Initval();
	CreateServ();

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(serverport);
	rc = bind(listen_sd, (struct sockaddr *)(&addr), sizeof(addr));
	if (rc < 0) {
		perror("bind() failed");
		close(listen_sd);
		exit(-1);
	}

	rc = listen(listen_sd, 32);
	if (rc < 0) {
		perror("listen() failed");
		close(listen_sd);
		exit(-1);
	}

	memset(fds, 0, sizeof(fds));

	fds[0].fd = listen_sd;
	fds[0].events = POLLIN;
	timeout = 30000 * 30000;
	while (end_server == 0)
	{
		if(Poll_addnewclient() == 0)
			break;

		current_size = nfds;
		for (i = 1; i < current_size; i++) {
			if (fds[i].revents == 0)
				continue;
			if (fds[i].fd == listen_sd) {
			}
			else {
				close_conn = 0;
				CheckMsg_isValid_send(usernickMap[fds[i].fd].get_holder());

				if (close_conn) {
					for (std::map<std::string, Channel>::iterator it = channelsMap.begin(); it != channelsMap.end();)
					{
						std::string channel_name = it->first;
						if (channelsMap[channel_name].get_is_member(fds[i].fd)){
							channelsMap[channel_name].leave_the_server(fds[i].fd);
							channelsMap[channel_name].broadcast(':' + usernickMap[fds[i].fd].get_nickname() + "!~" + usernickMap[fds[i].fd].get_username() + "@lcoalhost QUIT :Quit :Client closed connection", -1);
						}
						if (channelsMap[channel_name].get_current_users() == 0){
							it = channelsMap.erase(it);
						}
						else
							++it;
					}

					usernickMap.erase(fds[i].fd);
					close(fds[i].fd);
					compress_array = 1;
				}
			}
		}

		if (compress_array) {
			compress_array = 0;
			for (i = 0; i < nfds; i++) {
				if (fds[i].fd == -1) {
					for (j = i; j < nfds; j++)
						fds[j].fd = fds[j + 1].fd;
					i--;
					nfds--;
				}
			}
		}
	}
}


bool Server::Poll_addnewclient(){

		rc = poll(fds, nfds, timeout);

		if (rc < 0) {
			perror("poll() failed");
			return 0;
		}

		if (rc == 0) {
			std::cout << "poll() timed out. End program." << std::endl;
			return 0;
		}
		else if (fds[0].revents == POLLIN)
		{
			new_sd = accept(listen_sd, NULL, NULL);
			if (new_sd < 0) {
				if (errno != EWOULDBLOCK) {
					perror("accept() failed");
					end_server = 1;
				}
				return 0;
			}
			std::string clientIP = ClientIp(new_sd);
			std::cout << "New client connected from IP: " << clientIP << std::endl;
			usernickMap[new_sd] = Client();

			fds[nfds].fd = new_sd;
			fds[nfds].events = POLLIN ;
			nfds++;
		}
		return 1;
}

void Server::CheckMsg_isValid_send(std::string holder){

	if (fds[i].revents & POLLIN) {
		int found_delimiter = 0;

		while (!found_delimiter) {
			char recv_buffer[513];
			bzero(recv_buffer, sizeof(recv_buffer));
			rc = recv(fds[i].fd, recv_buffer, sizeof(recv_buffer), 0);
			if (rc == -1) {
				if (errno != EWOULDBLOCK) {
					close_conn = 1;
					break;
				}
				continue;
			}
			else if (rc == 0) {
				std::cout << "Connection closed" << std::endl;
				close_conn = 1;
				break;
			}
			else {
				recv_buffer[rc] = '\0';

				holder.append(recv_buffer, rc);
				bzero(recv_buffer, sizeof(recv_buffer));
				usernickMap[fds[i].fd].set_holder(holder);
				size_t pos = std::string::npos;
				if (holder.find("\r\n") != std::string::npos) {
					pos = holder.find("\r\n");
				}
				else if (holder.find("\n") != std::string::npos) {
					pos = holder.find("\n");
				}
				if (pos != std::string::npos) {
					found_delimiter = 1;
					std::string data = holder.substr(0, pos);
					usernickMap[fds[i].fd].set_holder("");
					this->receiveddata = parsdata(data);
					if (this->receiveddata.empty())
						std::cout << "wrong args\n";
					else
						check_reg_and_cmds(this->receiveddata, fds[i].fd);
				}
				break;
			}
		}
	}
}


bool Server::PasswordCheck(std::string pass){

	if (pass.empty() || pass.find_first_not_of(' ') == std::string::npos){
		std::cerr << "No password detected" << std::endl;
		return 0;
	}
	return 1;
}



std::string Server::getServerIp() {
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) == 0) {
		struct hostent* host = gethostbyname(hostname);
		if (host != NULL) {
			struct in_addr** addr_list = reinterpret_cast<struct in_addr**>(host->h_addr_list);
			if (addr_list[0] != NULL) {
				return inet_ntoa(*addr_list[0]);
			}
		}
	}
	return NULL;
}

std::string Server::getHostAdresse(){
	std::system( "ifconfig | grep 'inet ' | awk 'NR==2 {print $2}' > .log" );
	std::stringstream ss;
	ss << std::ifstream( ".log" ).rdbuf();
	std::system( "rm -f .log" );
	return (ss.str().substr( 0, ss.str().find( '\n' ) ));
}

std::string Server::ClientIp(int socket) {
	char buffer[INET_ADDRSTRLEN];
	struct sockaddr_in clientAddress;
	socklen_t addrLen = sizeof(clientAddress);

	if (socket >= 0 && getpeername(socket, (struct sockaddr*)&clientAddress, &addrLen) == 0) {
		if (inet_ntop(AF_INET, &clientAddress.sin_addr, buffer, INET_ADDRSTRLEN)) {
			this->localhost = buffer;
			if (localhost == "127.0.0.1")
				this->localhost = getHostAdresse();
			return localhost;
		}
		else {
			perror("inet_ntop() failed");
			return NULL;
		}
	}
	else {
		perror("getpeername() failed");
		return NULL;
	}
	return NULL;
}

int Server::get_sockfd(std::string usernickname){
	std::map<int, Client>::iterator it;
	for (it = usernickMap.begin(); it != usernickMap.end(); it++){
		if(it->second.get_nickname() == usernickname)
			return it->first;
	}
	return -1;
}

std::map<std::string, std::string> Server::get_channel_and_key(const std::vector<std::string>& receiveddata) {
	std::map<std::string, std::string> channelAndkey;

	if (receiveddata.size() == 2) {
		std::istringstream schannel(receiveddata[1]);

		std::string channel;

		while (std::getline(schannel, channel, ','))
				channelAndkey[channel] = "";
	}
	else if (receiveddata.size() >= 3) {
		std::istringstream schannel(receiveddata[1]);
		std::istringstream skey(receiveddata[2]);

		std::string channel;
		std::string key;

		while (std::getline(schannel, channel, ',')) {
			if (std::getline(skey, key, ','))
				channelAndkey[channel] = key;
			else
				channelAndkey[channel] = "";
		}
	}
	return channelAndkey;
}

Server::~Server() {
	std::cout << "this is destructor for our server" << std::endl;
}
