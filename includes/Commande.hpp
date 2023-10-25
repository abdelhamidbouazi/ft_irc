#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include "socket.hpp"

namespace HDE
{
    class Commande
    {
        private:
            std::vector<std::string> request;
            
        public:
            Commande();
            ~Commande();
            void	start_parssing(std::string& msg);
    };
}





#endif
