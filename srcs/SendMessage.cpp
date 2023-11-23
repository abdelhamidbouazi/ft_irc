#include "../includes/socket.hpp"
#include "../includes/Replies.hpp"

// this can be usefull for all mode
void HDE::SocketHde::sendMessageToAllForMODE(int i, std::string channelname, std::string message, std::string param)
{
    std::map<std::string, Channel*>::iterator it;
    for(it = channelsMap.begin(); it != channelsMap.end() ; ++it)
    {
        if(it->first == channelname)
        {
            std::vector<Client> tmp = it->second->getUsers();
            std::vector<int > add;
            std::vector<Client>::iterator itt;
            for(itt = tmp.begin(); itt != tmp.end(); itt++)
            {
                // if(itt->getNickname() != clt.at(fds[i].fd).getNickname())
                    add.push_back(itt->getClientId());
            }
            std::string nick = clt.at(fds[i].fd).getNickname();
			std::string selfStr = ":" + clt.at(fds[i].fd).getNickname()  + "!" + clt.at(fds[i].fd).getNickname() + "@" + clt.at(fds[i].fd).getLocalhost() + " MODE " +  channelname + " " + param + " " + message + "\r\n";
            for(size_t index = 0; index < add.size() ; index++)
                sendMessage(selfStr, add.at(index));
        }
    }
}



void HDE::SocketHde::sendMessageToAllForNICK(int i, std::string channelname, std::string newNick, std::string oldNick)
{
    std::map<std::string, Channel*>::iterator it;
    for(it = channelsMap.begin(); it != channelsMap.end() ; ++it)
    {
        if(it->first == channelname)
        {
            std::vector<Client> tmp = it->second->getUsers();
            std::vector<int > add;
            std::vector<Client>::iterator itt;
            for(itt = tmp.begin(); itt != tmp.end(); itt++)
            {
                // if(itt->getNickname() != clt.at(fds[i].fd).getNickname())
                    add.push_back(itt->getClientId());
            }
            std::string nick = clt.at(fds[i].fd).getNickname();
			std::string selfStr = ":" + oldNick  + "!" + oldNick + "@" + clt.at(fds[i].fd).getLocalhost() + " NICK " + ":" + newNick + "\r\n";
            for(size_t index = 0; index < add.size() ; index++)
                sendMessage(selfStr, add.at(index));
        }
    }
}
