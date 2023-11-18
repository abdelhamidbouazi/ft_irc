#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"

void HDE::SocketHde::Topic(std::vector<std::string> message, int i)
{
    if(message.size() == 1)
    {
        sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("TOPIC", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        return ;
    }
    else
    {
        if(channelsMap.find(message[1]) != channelsMap.end()  && message[1].at(0) == '#')
        {
            if(checkUserInChannel(channelsMap.at(message[1]), clt.at(fds[i].fd).getNickname()))
            {
                if(channelsMap.at(message[1])->getIsTopic() == false)
                {
                    sendMessage(":" + clt.at(fds[i].fd).getLocalhost() +  ERR_NOCHANMODES(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
                    return ;
                }
                if(checkUserInChannelOperator(channelsMap.at(message[1]), clt.at(fds[i].fd).getNickname()))
                {
                    if(message[2].empty())
                    {
                        sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + RPL_TOPIC(clt.at(fds[i].fd).getNickname(), message[1], channelsMap.at(message[1])->getTopic()), clt.at(fds[i].fd).getClientId());
                    }
                    else
                    {
                        if(message[2][0] == ':')
                        {
                            if(message[2][1])
                            {
                                std::string str = message[2].erase(0, 1);
                                channelsMap.at(message[1])->setTopic(str);
                                sendMessageToAllForTopic(i, message[1], 1);
                            }
                            else
                            {
                                channelsMap.at(message[1])->setTopic("");
                                sendMessageToAllForTopic(i, message[1], 0);
                            }
                        }
                    }
                }
                else
                {
                    if(message[2][0] == ':')
                    {
                        sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_CHANOPRIVSNEEDED(clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
                        return;
                    }
                    sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + RPL_TOPIC(clt.at(fds[i].fd).getNickname(), message[1], channelsMap.at(message[1])->getTopic()), clt.at(fds[i].fd).getClientId());
                }
            }
            else
            {
                sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOTONCHANNEL(message[1]), clt.at(fds[i].fd).getClientId());
                return;
            }
        }
        else
            sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHCHANNEL(message[1], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
    }
    return ;
}

void HDE::SocketHde::sendMessageToAllForTopic(int i, std::string channelname, int flag)
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
                add.push_back(itt->getClientId());
            }
            std::string nick = clt.at(fds[i].fd).getNickname();
            std::string selfStr;
            if (flag == 1)
                selfStr = ":" + clt.at(fds[i].fd).getLocalhost() + RPL_TOPIC(clt.at(fds[i].fd).getNickname(), channelname, channelsMap.at(channelname)->getTopic());
            else
                selfStr = ":" + clt.at(fds[i].fd).getLocalhost() + RPL_NOTOPIC(clt.at(fds[i].fd).getNickname(), channelname);
            for(size_t index = 0; index < add.size() ; index++)
                sendMessage(selfStr, add.at(index));
        }
    }
}
