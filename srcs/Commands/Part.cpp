#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"


std::vector<std::string> splitStringWithComma(std::string str) {
  std::vector<std::string> parts;
  std::stringstream ss(str);
  std::string part;
  while (std::getline(ss, part, ',')) {
    parts.push_back(part);
  }
  return parts;
}

bool HDE::SocketHde::checkUserInChannel(Channel *chan, std::string name)
{
    std::vector<Client>::iterator it ;
    for(it = chan->getUsers().begin(); it != chan->getUsers().end(); it++)
    {
        if(it->getNickname() == name)
            return true;
    }
    return false;
}
bool HDE::SocketHde::checkUserInChannelOperator(Channel *chan, std::string name)
{
    std::vector<Client>::iterator it ;
    for(it = chan->getOperators().begin(); it != chan->getOperators().end(); it++)
    {
        if(it->getNickname() == name)
            return true;
    }
    return false;
}
void HDE::SocketHde::Part(std::vector<std::string> message, int i)
{
    if(message.size() == 1)
    {
        sendMessage(":" + localhost + ERR_NEEDMOREPARAMS("PART", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        return ;
    }
    else
    {
        std::vector<std::string> channelToLeave = splitStringWithComma(message[1]);
        for(int index = 0; index < channelToLeave.size(); index++)
        {
            if(channelsMap.find(channelToLeave[index]) != channelsMap.end())
            {
                if(checkUserInChannel(channelsMap.at(channelToLeave[index]), clt.at(fds[i].fd).getNickname()))
                {
                    if(channelsMap.at(channelToLeave[index])->getHasOwner() &&  clt.at(fds[i].fd).getNickname() == channelsMap.at(channelToLeave[index])->getOwner())
                    {
                        channelsMap.at(channelToLeave[index])->setHasOwner(false);
                        channelsMap.at(channelToLeave[index])->setOwner("");
                    }
                    channelsMap.at(channelToLeave[index])->eraseUser(clt.at(fds[i].fd));
                    if(checkUserInChannelOperator(channelsMap.at(channelToLeave[index]), clt.at(fds[i].fd).getNickname()))
                        channelsMap.at(channelToLeave[index])->eraseOperator(clt.at(fds[i].fd));
                    if(channelsMap.at(channelToLeave[index])->getLimitUsers() != -1)
                        channelsMap.at(channelToLeave[index])->setlimitUsers(channelsMap.at(channelToLeave[index])->getLimitUsers() - 1 );
                    clt.at(fds[i].fd).setChannelCount(clt.at(fds[i].fd).getChannelCount() - 1);
                    sendMessageToAllForPart(i, channelToLeave[index]);
                }
                else
                {
                    sendMessage(":" + localhost + ERR_NOTONCHANNEL(channelToLeave[index]), clt.at(fds[i].fd).getClientId());
                    return;
                }
            }
            else
                sendMessage(":" + localhost + ERR_NOSUCHCHANNEL(channelToLeave[index], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        }
    }
}

void HDE::SocketHde::sendMessageToAllForPart(int i, std::string channelname)
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
                if(itt->getNickname() != clt.at(fds[i].fd).getNickname())
                    add.push_back(itt->getClientId());
            }
            std::string nick = clt.at(fds[i].fd).getNickname();
            std::string selfStr = ":" + nick  + "!" + nick + "@" + localhost + " PART " +  channelname + "\r\n";
            for(int index = 0; index < add.size() ; index++)
                sendMessage(selfStr, add.at(index));
        }
    }
}

