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
            std::string cmd;
            
        public:
            Commande();
            void	start_parssing(std::string& msg);
            void	join_strings_after_colon(std::vector<std::string>& line);

            std::string getCmd();
            void setCmd(std::string cmd);
            std::vector<std::string>	getRequest(void) const;
    };
}





#endif
