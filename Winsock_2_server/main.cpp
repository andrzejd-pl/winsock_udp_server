#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"

int main() {
	try {
		WSASession Session;
		UDPSocket Socket;
		char buffer[2];

		Socket.Bind(100);
		while (1) {
			sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));



			std::string input(buffer);
			std::reverse(std::begin(input), std::end(input));
			Socket.SendTo(add, input.c_str(), input.size());

		}
	}
	catch (std::system_error& e) {
		std::cout << e.what();
	}
	return 0;
}