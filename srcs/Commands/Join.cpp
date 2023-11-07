#include "../../includes/Commande.hpp"
#include "../../includes/Client.hpp"


void Join(std::vector<std::pair<std::string , std::string > > joinVector, Client &c ,std::map<std::string, Channel&> channelsMap)
{
    if(joinVector.empty())
    {
        // replies ERR_NEEDMOREPARAMS
        return ;
    }
    if(joinVector.size() == 1 && joinVector[0].first == "0")
    {
        //leave all the channel 
        // decrement the count of channel to 0 in the client 
        return ;
    }

    for(int i = 0; i <= joinVector.size(); i++)
    {
        
    }
}