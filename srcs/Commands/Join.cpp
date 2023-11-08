#include "../../includes/Commande.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/Replies.hpp"


void HDE::SocketHde::Join(std::vector<std::pair<std::string , std::string > > joinVector, int i)
{
    // std::cout << "size of the join vector" << joinVector.size() << std::endl;

    if(joinVector.empty())
    {
        std::cout << "empty\n";
        // replies ERR_NEEDMOREPARAMS
        sendMessage(localhost + ERR_NEEDMOREPARAMS("JOIN", clt.at(fds[i].fd).getNickname()), i);
        return ;
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