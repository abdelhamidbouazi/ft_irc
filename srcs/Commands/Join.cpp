#include "../../includes/Commande.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/Replies.hpp"


void HDE::SocketHde::Join(std::vector<std::pair<std::string , std::string > > joinVector, int i)
{
    if(joinVector.empty())
    {
        sendMessage(localhost + ERR_NEEDMOREPARAMS("JOIN", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        return;
    }
    if(joinVector.size() == 1 && joinVector[0].first == "0")
    {
        clt.at(fds[i].fd).setChannelCount(0);
        return ;
    }
    for(int index = 0; index < joinVector.size(); index++)
    {
        std::pair<std::string , std::string> temp = joinVector[index];
        if(temp.first[0] != '#')
            sendMessage(localhost + ERR_BADCHANMASK(temp.first, clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        else
        {
            if(channelsMap.find(temp.first) != channelsMap.end())
            {

                sendMessage("channel exit and you will join to it \n", clt.at(fds[i].fd).getClientId());
            }
            else
            {
                // Channel  addChannel(temp.first, clt.at(fds[i].fd), temp.second);
                // std::cout << "DEBUG\n";
                // channelsMap[temp.first] = addChannel;
                // std::cout << "DEBUG2\n";
                // // std::pair<std::string, Channel&> map(temp.first, addChannel);
                // // channelsMap.insert(map);
                // Channel* addChannel = new Channel(temp.first, clt.at(fds[i].fd), temp.second);
                // std::pair<std::string, Channel*> map(temp.first, addChannel);
                // channelsMap.insert(map);
                Channel* addChannel = new Channel(temp.first, clt.at(fds[i].fd), temp.second);
                channelsMap[temp.first] = addChannel;

                sendMessage("channel doesnt exit you will create it \n", clt.at(fds[i].fd).getClientId());
            }
        }
    }
    std::cout << "-----------------------\n";
    std::map<std::string, Channel*>::iterator it;
    for(it = channelsMap.begin(); it != channelsMap.end() ; ++it)
        std::cout<< " name inside the channel : "<< it->second->getChannelName() <<std::endl;

    // for (std::map<std::string, Channel&>::iterator it = channelsMap.begin(); it != channelsMap.end(); ++it)
    //     delete it->second;
}
