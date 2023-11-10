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

bool checkUserInChannel(Channel *chan, std::string name)
{
    std::vector<Client>::iterator it ;
    for(it = chan->getUsers().begin(); it != chan->getUsers().end(); it++)
    {
        if(it->getNickname() == name)
            return true;
    }
    return false;
}
bool checkUserInChannelOperator(Channel *chan, std::string name)
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
        sendMessage(localhost + ERR_NEEDMOREPARAMS("PART", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
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
                    }
                    std::vector<Client>::iterator it;
                    for(it = channelsMap.at(channelToLeave[index])->getOperators().begin(); it !=channelsMap.at(channelToLeave[index])->getOperators().end(); it++ )
                        std::cout << it->getNickname() << " =====users before erase\n" ;
                    channelsMap.at(channelToLeave[index])->eraseUser(clt.at(fds[i].fd));
                    if(checkUserInChannelOperator(channelsMap.at(channelToLeave[index]), clt.at(fds[i].fd).getNickname()))
                        channelsMap.at(channelToLeave[index])->eraseOperator(clt.at(fds[i].fd));
                    for(it = channelsMap.at(channelToLeave[index])->getOperators().begin(); it !=channelsMap.at(channelToLeave[index])->getOperators().end(); it++ )
                        std::cout << it->getNickname() << " =====users after erase\n" ;
                    
                }
                else
                {

                }

            }
            else
                sendMessage(localhost + ERR_NOSUCHCHANNEL(channelToLeave[index], clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        }
    }
}

