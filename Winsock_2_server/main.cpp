#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"
#include "Packet.h"
#include <vector>
#include <array>

#pragma comment (lib, "Ws2_32.lib")

/*
	TODO:
	- klasy dla ka�dego typu pakiet�w
	- wyj�tki i �apanie wyj�tk�w (zmiana w builderach z exception na w�asny autorski wyj�tek)
	- w�tki - 1 zarz�dzaj�cy - czyli main i 2 dla 2 klient�w
	- klasa klienta
*/

int main() {
	try {

		//	/*read address ip sender's*/
		//
		//	char ip[20];
		//	InetNtop(AF_INET, &(add.sin_addr.s_addr), ip, 20);
		//
		//	/*-----------------*/

		WSASession session;
		UDPSocket socket;
		std::vector<char> buffer(2);

		

		unsigned int client_id = 1;
		std::array<unsigned short, 2> numbersL;

		socket.Bind(100);
		while (true) {
			sockaddr_in add = socket.RecvFrom(buffer.data(), buffer.size());
			Packet packet = Packet::GenerateIdPacketBuilder().build(buffer);

			if (packet.getOperation() != 0) {
				/*  koniec po��czenia  */
				packet = Packet::EndPacketBuilder().set_id(0).build();

				socket.SendTo(add, packet.convertToSend());

				continue;
			}

		}
	}
	catch (std::system_error& e) {
		std::cout << e.what();
	}
	return 0;
}