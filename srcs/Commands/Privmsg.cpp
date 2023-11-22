#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"


std::vector<std::string> splitPrivmsgArgs(std::string message)
{
    std::vector<std::string> target;
    size_t pos;
    while(1)
    {
        pos = message.find(",");
        target.push_back(message.substr(0, pos));
        message.erase(0, pos + 1);
        if(pos == std::string::npos)
            break;
    }
    return target;
}

int GetUserIdByName(std::map<std::string, int> &AllUsers, std::string name)
{
    std::map<std::string, int>::iterator it = AllUsers.find(name);

    if (it == AllUsers.end())
        return -1;
    else
    {
        int id = it->second;
        return id;
    }
}
void HDE::SocketHde::Privmsg(std::vector<std::string> message, int i)
{
    std::vector<std:: string> target = splitPrivmsgArgs(message[1]);
    if(target.size() > MAX_TARGET)
    {
        sendMessage((":" + clt.at(fds[i].fd).getLocalhost() + ERR_TOOMANYTARGETS(target[0])), clt.at(fds[i].fd).getClientId());
        return;
    }
    if(message.size() == 1)
    {
        sendMessage((":" + clt.at(fds[i].fd).getLocalhost() + ERR_NORECIPIENT(message[0])), clt.at(fds[i].fd).getClientId());
        return;
    }
    else if(message.size() == 2)
    {
        sendMessage((":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOTEXTTOSEND), clt.at(fds[i].fd).getClientId());
        return;
    }

    if(message[1][0] == '#')
    {
        if(channelsMap.find(message[1]) != channelsMap.end() && message[1].at(0) == '#')
        {
            if(checkUserInChannel(channelsMap.at(message[1]), clt.at(fds[i].fd).getNickname()))
            {
                sendMessageToAllForPrivmsg(i, message[1], message[2]);
                return ;
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
    else
    {
        if(GetUserIdByName(AllUsers, message[1]) != -1)
        {
            int k = GetUserIdByName(AllUsers, message[1]);
            std::string nick = clt.at(fds[i].fd).getNickname();
            std::string username = clt.at(fds[i].fd).getUsername();
            std::string selfStr = ":" + nick + "!" + username + "@" + clt.at(fds[i].fd).getLocalhost() + " PRIVMSG " + clt.at(fds[k].fd).getNickname() + " :"+ message[2] + "\r\n";
            sendMessage(selfStr, clt.at(fds[k].fd).getClientId());
        }
        else
            sendMessage(":" + clt.at(fds[i].fd).getLocalhost() + ERR_NOSUCHNICK(clt.at(fds[i].fd).getNickname() , message[1]), clt.at(fds[i].fd).getClientId());
        return ;
    }
}



void HDE::SocketHde::sendMessageToAllForPrivmsg(int i, std::string channelname, std::string message)
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
            std::string selfStr = ":" + nick  + "!" + nick + "@" + clt.at(fds[i].fd).getLocalhost() + " PRIVMSG " +  channelname + " :" + message + "\r\n";
            for(size_t index = 0; index < add.size() ; index++)
                sendMessage(selfStr, add.at(index));
        }
    }
}

// std::string reply = ":" + clt.at(fds[i].fd).getLocalhost() + " 001 " + clt.at(fds[i].fd).getNickname();
// reply += " :Welcome to the Internet Relay Network " +  clt.at(fds[i].fd).getNickname() + "\n";
// reply += ":" + clt.at(fds[i].fd).getLocalhost() + " 002 " + clt.at(fds[i].fd).getNickname();
// reply += " :Your host is " + clt.at(fds[i].fd).getLocalhost() + ", running version 1.0\n";
// reply += ":" + clt.at(fds[i].fd).getLocalhost() + " 003 " + clt.at(fds[i].fd).getNickname() + " :This server was created\n";
// reply += ":" + clt.at(fds[i].fd).getLocalhost() + " 004 " + clt.at(fds[i].fd).getNickname();
// reply += " " + clt.at(fds[i].fd).getLocalhost() + " 1.0\n";
// sendMessage(reply, clt.at(fds[i].fd).getClientId());
