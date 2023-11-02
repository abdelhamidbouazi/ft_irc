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
		this->cmd = msg.substr(0, pos);
		std::transform(this->cmd.begin(), this->cmd.end(), this->cmd.begin(), ::toupper);

		if(this->cmd == "USER" || this->cmd == "PRIVMSG"
			|| this->cmd == "TOPIC" || this->cmd == "PART" || this->cmd == "KICK")
        {
            size_t pos ;
            while (true)
            {
                pos = msg.find(dl);
                request.push_back(msg.substr(0, pos));
                msg.erase(0, pos + dl.length());
                if(pos == std::string::npos)
                    break;
            }
			join_strings_after_colon(this->request);
		}

		else if(this->cmd == "INVITE" || this->cmd == "MODE"
                || this->cmd == "PASS" || this->cmd == "NICK")
        {
            size_t pos ;
            while (true)
            {
                pos = msg.find(dl);
                this->request.push_back(msg.substr(0, pos));
                msg.erase(0, pos + dl.length());
                if(pos == std::string::npos)
                    break;
            }
        }
		// for (int i = 0; i< request.size(); i++)
		// 	std::cout << "request[" << i << "] ===> "<< request[i] << std::endl;
		// else if(this->cmd == "JOIN")
        // {
	    // }
    }
	else 
	{
        this->cmd = msg;
		std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
	}
}


void	HDE::Commande::join_strings_after_colon(std::vector<std::string>& line){
	std::string	temp;
	bool	flag = false;
	std::vector<std::string>::iterator saver = line.end();
	for (std::vector<std::string>::iterator it = line.begin(); it != line.end(); ++it){
		if ((*it)[0] == ':'){
			flag = true;
			temp = *it;
			saver = it;
		}
		else if (flag)
			temp += " " + *it;
	}
	if (saver != line.end()) {
		line.erase(saver, line.end());
	}
	line.push_back(temp);
}

std::string HDE::Commande::getCmd()
{
    return this->cmd;
}


void HDE::Commande::setCmd(std::string cmd)
{
    this->cmd = cmd;
}
std::vector<std::string> HDE::Commande::getRequest(void) const
{
    return this->request;
}