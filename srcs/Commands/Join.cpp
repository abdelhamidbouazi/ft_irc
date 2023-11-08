#include "../../includes/Commande.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/Replies.hpp"


void HDE::SocketHde::Join(std::vector<std::pair<std::string , std::string > > joinVector, int i)
{
    // std::cout << "size of the join vector" << joinVector.size() << std::endl;

    // for ( std::vector < std::pair<std::string ,std::string> >::const_iterator it = joinVector.begin() ; it != joinVector.end(); it++){
    //     std::cout << "first: "<< it->first << "second: " << it->second << std::endl;
    // }
    // std::map<int, Client>::iterator it;
    // for (it = clt.begin(); it != clt.end(); ++it) {
    //     int key = it->first;           // Access the key
    //     Client& client = it->second;   // Access the value (Client object)

    //     std::cout << "id: " << key << " name: " << client.getNickname() << std::endl;
    // }

    if(joinVector.empty())
    {
        sendMessage(localhost + ERR_NEEDMOREPARAMS("JOIN", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        return;
    }
    if(joinVector.size() == 1 && joinVector[0].first == "0")
    {
        // leave all the channel 
        // decrement the count of channel to 0 in the client 

        clt.at(fds[i].fd).setChannelCount(0);
        return ;
    }
    for(int index = 0; index < joinVector.size(); index++)
    {
        // ERR_NEEDMOREPARAMS(clt.at(fds[i].fd));
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
                Channel addChannel(temp.first, clt.at(fds[i].fd), temp.second);

                // Channel addChannel = new Channel(temp.first, clt.at(fds[i].fd), temp.second);
                std::pair<std::string, Channel&> map(temp.first, addChannel);
                map.first = temp.first;
                map.second = addChannel;
                channelsMap.insert(map);
                // delete addChannel;
                sendMessage("channel doesnt exit you will create it \n", clt.at(fds[i].fd).getClientId());

            }
        }
        // std::cout << "first: "<<joinVector[i].first << " second: " << joinVector[i].second << std::endl;
    }
    // std::map<std::string, Channel&>::iterator it;
    // for (it = channelsMap.begin(); it != channelsMap.end(); ++it) {
    //     std::string  name = it->first;           // Access the key
    //     Channel channel = it->second;   // Access the value (Client object)

    //     std::cout << "name: " << name << " channel class: " << it->second.getChannelName() <<std::endl;
    //     // std::cout << "id: " << key << " name: " << client.getNickname() << std::endl;
    // }
}