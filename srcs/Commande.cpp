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

		else if(this->cmd == "INVITE" || this->cmd == "PASS" || this->cmd == "NICK")
        {
			pushToVector(this->request, msg);
        }
		else if(this->cmd == "MODE")
		{
			pushToVectorForMode(this->request, msg);
		}
		else if(this->cmd == "JOIN")
        {
			pushToVector(this->request, msg);
			splitTheJoinPram();
			// for ( std::vector < std::pair<std::string, std::string> >::const_iterator it = this->modeVect.begin() ; it != this->modeVect.end(); it++){
    	    // 	std::cout << it->first << "-------" << it->second << std::endl;  
			// }
		}
    }
	else
	{
        this->cmd = msg;
		std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
	}
}


void HDE::Commande::splitTheJoinPram()
{
	std::string tmp;
	size_t pos_tmp;
	size_t pos_chann;
	int first = 1;
	std::string dlMode = ",";
	
	if(this->request.size() <= 3)
	{
		while (1)
		{
			pos_chann = this->request[1].find(dlMode);
			if (this->request.size() == 3 && first){
				pos_tmp = this->request[2].find(dlMode);
				tmp = this->request[2].substr(0, pos_tmp);
				this->request[2].erase(0, pos_tmp + dlMode.length());
				if (pos_tmp == std::string::npos)
					first = 0;
			}
			else
				tmp = "";

			this->modeVect.push_back(std::make_pair(this->request[1].substr(0, pos_chann), tmp));	
			this->request[1].erase(0, pos_chann + dlMode.length());
			if (pos_chann == std::string::npos)
				break;
		}
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
void pushToVectorForMode(std::vector<std::string> &vec, std::string str)
{
	std::string dl = " " ;
	size_t pos ;
	int i = 0;
	while (true)
	{
		i++;
		pos = str.find(dl);
		if(i == 3)
		{
			vec.push_back(str.substr(0, 1));
			vec.push_back(str.substr(1, pos));
		}
		else
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

std::vector<std::string> HDE::Commande::getRequest()
{
	return this->request;
}

std::vector<std::pair<std::string, std::string> > HDE::Commande::getModeVect()
{
    return this->modeVect;
}

void HDE::Commande::setCmd(std::string cmd)
{
    this->cmd = cmd;
}

void HDE::Commande::setRequest(std::vector<std::string> request)
{
	this->request = request;
}
void HDE::Commande::setModeVect(std::vector<std::pair<std::string, std::string> > Modevect)
{
	this->modeVect = Modevect;
}
