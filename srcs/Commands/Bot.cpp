#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Replies.hpp"
#include "../../includes/socket.hpp"  


void HDE::SocketHde::Bot(int i)
{
   std::time_t now = std::time(nullptr);
   std::time_t elapsed_time = now - clt.at(fds[i].fd).getStartTime();
    int hours = elapsed_time / 3600;
    int minutes = (elapsed_time % 3600) / 60;
    int seconds = elapsed_time % 60;
    std::string times =  " the time you spend in this server : " + std::to_string(hours) + " hours, " + std::to_string(minutes) + " minutes, " + std::to_string(seconds) + " seconds\n"; 
    sendMessage(":" + localhost + times, clt.at(fds[i].fd).getClientId());
}