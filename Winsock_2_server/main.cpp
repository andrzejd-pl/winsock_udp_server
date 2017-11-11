#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"
#include "Packet.h"
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

int main() {
	try {
		WSASession Session;
		UDPSocket Socket;
		char buffer[3];

		Socket.Bind(100);
		while (1) {
			sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));

			Packet packet(buffer, 2);
			sockaddr* sock = reinterpret_cast<sockaddr *>(&add);
			IN_ADDR addr = add.sin_addr;
			char ip[20];

			InetNtop(AF_INET, &(add.sin_addr.s_addr), ip, 20);

			std::cout << "Packet from: " << ip << std::endl;

			std::string input(buffer);
			
			Socket.SendTo(add, input.c_str(), input.size());

		}
	}
	catch (std::system_error& e) {
		std::cout << e.what();
	}
	return 0;
}