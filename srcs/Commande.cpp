#include "../includes/Commande.hpp"


HDE::Commande::Commande()
{
}

// void HDE::Commande::start_parssing(std::string& msg, int i)
// {
// 	std::string dl = " " ;
// 	size_t pos = msg.find(dl);

// 	if(pos != std::string::npos)
// 	{
// 		std::string cmd = msg.substr(0, pos);
// 		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
// 		// msg.erase(0, pos + dl.length());
// 		if(cmd == "PASS" || cmd == "NICK")
// 		{
// 			request.push_back(msg.substr(0, pos));
// 			request.push_back(msg.substr(pos + 1, msg.length()));
// 		}

// 		else if(cmd == )
// 		for (int i = 0; i< request.size(); i++)
// 			std::cout << "request[" << i << "] ===> "<< request[i] << std::endl;
// 		// else if(cmd == "USER" || cmd == "PRIVMSG"
// 		// 	|| cmd == "TOPIC" || cmd == "PART"
// 		// 	|| cmd == "QUIT" || cmd == "NOTICE"
// 		// 	|| cmd == "OPER" || cmd == "KICK")
//         // {
// 		// 	// this->request = _split(msg, dl);
// 		// 	// join_strings(this->request);
// 		// }
// 		// else if(cmd == "INVITE" || cmd == "MODE"
// 		// 	|| cmd == "LIST" || cmd == "NAMES")
// 		// 	// this->request = _split(msg, dl);
// 		// else if(cmd == "JOIN")
//         // {
// 		// 	std::string dl = ",";
// 		// 	// this->_request = _splitJOIN(msg, dl);
// 	    // }
//     }
// 	else 
// 	{
// 		// this->cmd = msg;
// 		std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
// 	}
// }



void HDE::Commande::start_parssing(std::string& msg, int i)
{
	std::string dl = " " ;
	size_t pos = msg.find(dl);

	if(pos != std::string::npos)
	{
		std::string cmd = msg.substr(0, pos);
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
		// msg.erase(0, pos + dl.length());
		if(cmd == "PASS" || cmd == "NICK")
		{
			request.push_back(msg.substr(0, pos));
			request.push_back(msg.substr(pos + 1, msg.length()));
		}

		// else if(cmd == )
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




// void server::parseDataAndRespond(size_t pos) {
//     std::vector<std::string>    cmdVec;
//     std::string                 msg(_buff);
//     size_t                      msgEnd;
//     char                        str[512];

//     std::string     str1;
//     std::string     cm;

//     msgEnd = msg.find_first_of("\r\n");
//     if (msgEnd == std::string::npos)
//         _connectedClients.at(_fdsVec.at(pos).fd).clientBuff += msg;
//     else {
//         _connectedClients.at(_fdsVec.at(pos).fd).clientBuff += msg.substr(0, msgEnd);
//         std::strcpy(str, _connectedClients.at(_fdsVec.at(pos).fd).clientBuff.c_str());

//         str1 = _connectedClients.at(_fdsVec.at(pos).fd).clientBuff;

//         int i = 0;
//         int j = 0;
//         while (i < (int)str1.size())
//         {
//             if (str1[i] == ' ')
//                 i++;
//             if (str1[i] == ':')
//             {
//                 j = 0;
//                 i++;
//                 while (str1[i] && j < (int)str1.size())
//                     str[j++] = str1[i++];
//                 str[j] = '\0';
//                 cmdVec.push_back(str);
//                 break;
//             }
//             j = 0;
//             while (str1[i] && (str1[i] != ' '))
//                 str[j++] = str1[i++];
//             str[j] = '\0';
//             cmdVec.push_back(str);
//             i++;
//         }
//         if (!cmdVec.empty())
//             std::transform(cmdVec[0].begin(), cmdVec[0].end(), cmdVec[0].begin(), ::tolower);
//         _connectedClients.at(_fdsVec.at(pos).fd).clientBuff.clear();
//         respondToClient(cmdVec, _connectedClients.find(_fdsVec.at(pos).fd));
//     }
// }
