#include "../../includes/socket.hpp"

bool HDE::SocketHde::CheckQUIT(std::vector<std::string> message, int i) {
    if (message.size() != 1){
        std::cout << "args error" <<std::endl;
        return false;
    }

    User* user = identifyUser(fds[i].fd); // You need to implement this function

    client.removeUser(user); // You need to implement this function

    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
        it->removeUser(user); // You need to implement this function
        if (it->isOperator(user)) { // You need to implement this function
            it->removeOperator(user); // You need to implement this function
        }
    }

    close(fds[i].fd);
    return false;
}
