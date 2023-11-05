#include "../includes/Commande.hpp"


HDE::Commande::Commande()
{
}

std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}


void HDE::Commande::start_parssing(std::string& msg)
{
	std::string dl = " " ;
	msg = trim(msg);
	size_t pos = msg.find(dl);

	if(pos != std::string::npos)
	{
		this->cmd = msg.substr(0, pos);
		std::transform(this->cmd.begin(), this->cmd.end(), this->cmd.begin(), ::toupper);
		if(this->cmd == "USER" || this->cmd == "PRIVMSG"
			|| this->cmd == "TOPIC" || this->cmd == "PART" || this->cmd == "KICK")
        {
			pushToVector(this->request, msg);
			join_strings_after_colon(this->request);
		}

		else if(this->cmd == "INVITE" || this->cmd == "MODE"
                || this->cmd == "PASS" || this->cmd == "NICK")
        {
			pushToVector(this->request, msg);
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


void pushToVector(std::vector<std::string> &vec, std::string str)
{
	std::string dl = " " ;
	size_t pos ;
	while (true)
	{
		pos = str.find(dl);
		vec.push_back(str.substr(0, pos));
		str.erase(0, pos + dl.length());
		if(pos == std::string::npos)
			break;
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
			temp.erase(0, 1);
			saver = it;
		}
		else if (flag)
			temp += " " + *it;
	}
	if (saver != line.end()) {
		line.erase(saver, line.end());
	}
	if(flag)
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

std::vector<std::string> HDE::Commande::getRequest()
{
	return this->request;
}

void HDE::Commande::setRequest(std::vector<std::string> request)
{
	this->request = request;
}
