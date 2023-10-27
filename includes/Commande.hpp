#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include "socket.hpp"
#include <vector>


namespace HDE
{
    class Commande
    {
        private:
            std::vector<std::string> request;
            
        public:
            Commande();
            void	start_parssing(std::string& msg, int i);
            void	join_strings_after_colon(std::vector<std::string>& line);
            std::vector<std::string> split_commande(std::string& line, std::string& delim);

    };
}





#endif
