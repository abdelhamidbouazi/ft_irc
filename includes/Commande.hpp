#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include "socket.hpp"
#include "Client.hpp"


namespace HDE
{
    class Commande
    {
        private:
            std::vector<std::string> request;
            std::vector<std::pair<std::string , std::string > > joinVector;
            
        public:
            Commande();

            void	start_parssing(std::string& msg);
            void	join_strings_after_colon(std::vector<std::string>& line, int i);

            std::string getCmd();
            std::vector<std::string> getRequest();
            std::vector<std::pair<std::string, std::string > > getJoinVector();

            void setCmd(std::string cmd);
            void setRequest(std::vector<std::string> request);
            void setJoinVector(std::vector<std::pair<std::string, std::string> > joinVector);

            void splitTheJoinPram();
    };
}

void pushToVector(std::vector<std::string> &vec, std::string str);
void pushToVectorForMode(std::vector<std::string> &vec, std::string str);

#endif
