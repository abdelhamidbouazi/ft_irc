#include "../../includes/Commande.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/Replies.hpp"

bool IsClientInVector(std::vector<Client> users, Client client)
{
	for (std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it->getNickname() == client.getNickname())
		{
			return true;
		}
	}
	return false;
}
bool IsInInvitedUser(std::vector<std::string> invitedUser, std::string name)
{
	std::vector<std::string>::iterator it = find(invitedUser.begin(), invitedUser.end(), name);
	if (it == invitedUser.end())
		return false;
	else
		return true;
}

void HDE::SocketHde::Join(std::vector<std::pair<std::string, std::string > > joinVector, int i)
{
    if(joinVector.empty())
    {
        sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NEEDMOREPARAMS("JOIN", clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        return;
    }
    if(joinVector.size() == 1 && joinVector[0].first == "0")
    {
        clt.at(fds[i].fd).setChannelCount(0);
        std::map<std::string, Channel*>::iterator it;
        for(it = channelsMap.begin() ; it != channelsMap.end(); it++)
        {
            if(IsClientInVector(it->second->getUsers(), clt.at(fds[i].fd)))
            {
                it->second->eraseUser(clt.at(fds[i].fd));
                if(it->second->getHasOwner() &&  clt.at(fds[i].fd).getNickname() == it->second->getOwner())
                {
                    it->second->setHasOwner(false);
                    it->second->setOwner("");
                }
                if(it->second->getLimitUsers() != -1)
                    it->second->setlimitUsers(it->second->getLimitUsers() - 1 );
                sendMessageToAllForPart(i, it->second->getChannelName());
            }
        }
        return ;
    }
    for(int index = 0; index < joinVector.size(); index++)
    {
        std::pair<std::string , std::string> temp = joinVector[index];
        if(temp.first[0] != '#')
            sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_BADCHANMASK(temp.first, clt.at(fds[i].fd).getNickname()), clt.at(fds[i].fd).getClientId());
        else
        {
            if(channelsMap.find(temp.first) != channelsMap.end())
            {
                std::vector<Client> tmpVector = channelsMap.at(temp.first)->getUsers();
                if(clt.at(fds[i].fd).getChannelCount() >= USER_MAX_CHANNEL)
                {
                    sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_TOOMANYCHANNELS(temp.first, clt.at(fds[i].fd).getNickname()),clt.at(fds[i].fd).getClientId());
                    return;
                }
                if(channelsMap.at(temp.first)->getLimitUsers() != -1 && channelsMap.at(temp.first)->getUsers().size() >= channelsMap.at(temp.first)->getLimitUsers())
                {
                    sendMessage(":" + clt.at(fds[i].fd).getLocalhost() +  ERR_CHANNELISFULL(temp.first, clt.at(fds[i].fd).getNickname()),clt.at(fds[i].fd).getClientId());
                    return ;
                }
                else if(IsClientInVector(channelsMap.at(temp.first)->getUsers(), clt.at(fds[i].fd))) 
                {
                    sendMessage(":" + clt.at(fds[i].fd).getLocalhost() +  ERR_CHANNELISFULL(temp.first, clt.at(fds[i].fd).getNickname()),clt.at(fds[i].fd).getClientId());
                    return ;
                }
                else if(channelsMap.at(temp.first)->getLimitUsers() == -1)
                {
                    if(channelsMap.at(temp.first)->getKey().length() != 0)
                    {
                        if(channelsMap.at(temp.first)->getKey() == temp.second)
                        { 
                            bool invite_only = channelsMap.at(temp.first)->getInvite_only();
                            bool invited_user = IsInInvitedUser(channelsMap.at(temp.first)->getInvitedUser(), clt.at(fds[i].fd).getNickname());
                            if(invite_only && !invited_user)
                            {
                                sendMessage(":" + clt.at(fds[i].fd).getLocalhost() +  ERR_INVITEONLYCHAN(temp.first, clt.at(fds[i].fd).getNickname()),clt.at(fds[i].fd).getClientId());
                                return ;
                            }
                            if(invite_only && invited_user || !invite_only)
                            {
                                clt.at(fds[i].fd).setChannelCount(clt.at(fds[i].fd).getChannelCount() + 1);
                                channelsMap.at(temp.first)->addUsers(clt.at(fds[i].fd));
                                sendMessageToAll(i, temp.first);
                            }
                        }
                        else
                        {
                            sendMessage(":" + clt.at(fds[i].fd).getLocalhost() +  ERR_BADCHANNELKEY(temp.first, clt.at(fds[i].fd).getNickname()),clt.at(fds[i].fd).getClientId());
                            return ;
                        }
                    }
                    else
                    {
                        bool invite_only = channelsMap.at(temp.first)->getInvite_only();
                        bool invited_user = IsInInvitedUser(channelsMap.at(temp.first)->getInvitedUser(), clt.at(fds[i].fd).getNickname());
                        if(invite_only && !invited_user)
                        {
                            sendMessage(":" + clt.at(fds[i].fd).getLocalhost() +  ERR_INVITEONLYCHAN(temp.first, clt.at(fds[i].fd).getNickname()),clt.at(fds[i].fd).getClientId());
                            return ;
                        }
                        if(invite_only && invited_user || !invite_only)
                        {
                            clt.at(fds[i].fd).setChannelCount(clt.at(fds[i].fd).getChannelCount() + 1);
                            channelsMap.at(temp.first)->addUsers(clt.at(fds[i].fd));
                            sendMessageToAll(i, temp.first);
                            if(invite_only && invited_user)
                                channelsMap.at(temp.first)->eraseInvitedUser(clt.at(fds[i].fd).getNickname());
                        }
                    }
                }
            }
            else
            {
                if(clt.at(fds[i].fd).getChannelCount() >= USER_MAX_CHANNEL)
                {
                    sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_TOOMANYCHANNELS(temp.first, clt.at(fds[i].fd).getNickname()),clt.at(fds[i].fd).getClientId());
                    return;
                }
                clt.at(fds[i].fd).setChannelCount(clt.at(fds[i].fd).getChannelCount() + 1);
                Channel* addChannel = new Channel(temp.first, clt.at(fds[i].fd), temp.second);
                channelsMap[temp.first] = addChannel;
                sendMessageToAll(i, temp.first);\
            }
        }
    }
    std::cout << "-----------------------\n";
    std::map<std::string, Channel*>::iterator it;
    for(it = channelsMap.begin(); it != channelsMap.end() ; ++it)
        std::cout<< " name inside the channel : "<< it->second->getChannelName() <<std::endl;
    // u should delete the addchannel to avoid the leaks 
}

void HDE::SocketHde::sendMessageToAll(int i, std::string channelname)
{
	std::string nick = clt.at(fds[i].fd).getNickname();
	std::string selfStr = ":" + nick + "!" + nick + "@" + clt.at(fds[i].fd).getLocalhost() + " JOIN " + channelname + "\r\n";
	sendMessage(selfStr, clt.at(fds[i].fd).getClientId());

	std::string usersName = "";
	std::map<std::string, Channel *>::iterator it;
	for (it = channelsMap.begin(); it != channelsMap.end(); ++it)
	{
		if (it->first == channelname)
		{
			std::vector<Client> tmp = it->second->getUsers();
			std::vector<int> add;
			std::vector<Client>::iterator itt;
			for (itt = tmp.begin(); itt != tmp.end(); itt++)
			{
				if (itt->getNickname() != it->second->getOwner())
					usersName += itt->getNickname() + " ";
				if (itt->getNickname() != clt.at(fds[i].fd).getNickname())
					add.push_back(itt->getClientId());
			}
			std::string msjj = ":" + clt.at(fds[i].fd).getLocalhost() + " 353 " + clt.at(fds[i].fd).getNickname() + " = " + channelname + " :" + usersName;
			if (it->second->getHasOwner())
			{
				msjj += "@" + it->second->getOwner();
			}
			msjj += "\r\n:" + clt.at(fds[i].fd).getLocalhost() + " 366 " + clt.at(fds[i].fd).getNickname() + " " + channelname + " :End of /NAMES list\r\n";
			sendMessage(msjj, clt.at(fds[i].fd).getClientId());
			for (int index = 0; index < add.size(); index++)
				sendMessage(selfStr, add.at(index));
		}
	}
}
