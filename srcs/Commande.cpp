#include "../includes/Commande.hpp"


HDE::Commande::Commande()
{
}


void HDE::Commande::start_parssing(std::string& msg)
{
	std::string dl = " " ;
	size_t pos = msg.find(dl);

	if(pos != std::string::npos)
	{
		std::string cmd = msg.substr(0, pos);
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
		// msg.erase(0, pos + dl.length());
		// if(cmd == "PASS" || cmd == "NICK")
			// request.push_back(msg.substr(0, msg.length()));

		request.push_back(msg.substr(0, pos));
		request.push_back(msg.substr(pos + 1, msg.length()));
		
		// std::cout << msg.substr(0, msg.length()) << std::endl;
		for (int i = 0; i< request.size(); i++)
			std::cout << "request[" << i << "] ===> "<< request[i] << std::endl;
		// else if(cmd == "USER" || cmd == "PRIVMSG"
		// 	|| cmd == "TOPIC" || cmd == "PART"
		// 	|| cmd == "QUIT" || cmd == "NOTICE"
		// 	|| cmd == "OPER" || cmd == "KICK")
        // {
		// 	// this->request = _split(msg, dl);
		// 	// join_strings(this->request);
		// }
		// else if(cmd == "INVITE" || cmd == "MODE"
		// 	|| cmd == "LIST" || cmd == "NAMES")
		// 	// this->request = _split(msg, dl);
		// else if(cmd == "JOIN")
        // {
		// 	std::string dl = ",";
		// 	// this->_request = _splitJOIN(msg, dl);
	    // }
    }
	else 
	{
		// this->cmd = msg;
		std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
	}


}
