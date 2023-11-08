#include "../includes/Args.hpp"
#include "../includes/Client.hpp"
#include "../includes/Channel.hpp"
#include "../includes/TestServer.hpp"

int main(int ac, char **av){

	if (ac != 3)
	{
		std::cout << "Error: Check Arguments;" << std::endl;
		return 1;
	}
	try {
		Args	a(av[1], av[2]);
		Client	c(5);

		// Channel ch("channel1", c);


		// // std::cout << ch.getChannel() << "\n";
		// // ch.addUsers(c);
		// // ch.addUsers(c2);

		// for (int i = 0; i < ch.getUsers().size(); i++){
		// 	std::cout << "Users in the vector are : " << ch.getUsers().at(i).getUsername() << std::endl;
		// }
		// std::cout <<std::endl;

		c.addUser("abouazi", c);
		c.setNickname("opus");

		// Server(a.getPort(), a.getPassword());
		HDE::TestServer ts(a.getPort(), a.getPassword());
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}


// #include <iostream>
// #include <map>
// #include <string>

// int main() {
//     Client c1(12);
//     Client c2(13);
//     Client c3(13);
//     std::map<std::string, Client*> mymap;
//     std::string str1 = "Abd1";
//     std::string str2 = "Abd2";
//     std::string str3 = "Abd3";

//     mymap[str1] = &c1;
//     mymap[str2] = &c2;
//     mymap[str3] = &c3;

//     std::cout << "mymap['Abd1'] is " << mymap[str1]->getClientId() << '\n';
//     std::cout << "mymap['Abd2'] is " << mymap[str2]->getClientId() << '\n';
//     std::cout << "mymap['Abd3'] is " << mymap[str3]->getClientId() << '\n';

//     std::cout << "mymap now contains " << mymap.size() << " elements.\n";

//     return 0;
// }
