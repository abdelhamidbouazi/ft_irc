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
        return ;
    }
    std::cout << "the size of the joinvector: " << joinVector.size() << std::endl;
    for(int i = 0; i < joinVector.size(); i++)
    {
        // ERR_NEEDMOREPARAMS(clt.at(fds[i].fd));

        std::cout << "first: "<<joinVector[i].first << " second: " << joinVector[i].second << std::endl;
    }
}