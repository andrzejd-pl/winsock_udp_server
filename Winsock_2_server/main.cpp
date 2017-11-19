#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"
#include "Packet.h"
#include <WS2tcpip.h>
#include <vector>
#include <array>

#pragma comment (lib, "Ws2_32.lib")

/*
	TODO:
	- klasy dla ka¿dego typu pakietów
	- wyj¹tki
*/

int main() {
	try {

		//WSASession Session;
		//UDPSocket Socket;
		//char buffer[3];
		//
		//Socket.Bind(100);
		//while (1) {
		//	sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));
		//
		//	Packet packet(buffer, 2);
		//
		//	/*read address ip sender's*/
		//
		//	char ip[20];
		//	InetNtop(AF_INET, &(add.sin_addr.s_addr), ip, 20);
		//
		//	/*-----------------*/
		//
		//	std::cout << "Packet from " << ip << " contains fields:" <<
		//		"\n\t" << "operation - " << packet.getOperation() <<
		//		"\n\t" << "response - " << packet.getResponse() <<
		//		"\n\t" << "id - " << packet.getId() <<
		//		std::endl;
		//
		//	packet = Packet::PacketBuilder()
		//		.set_operation(0)
		//		.set_response(0)
		//		.set_id(0)
		//		.build();
		//
		//	std::string input(packet.convertToSend());
		//
		//	Socket.SendTo(add, input.c_str(), input.size());
		//
		//}

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
				/*  koniec po³¹czenia  */
				packet = Packet::EndPacketBuilder().set_id(0).build();

				socket.SendTo(add, packet.convertToSend());

				continue;
			}

			//pierwszy pakiet ack
			packet = Packet::AckPacketBuilder()
				.set_id(0)
				.build();

			socket.SendTo(add, packet.convertToSend());

			//pakiet z id dla klienta
			packet = Packet::GenerateIdPacketBuilder()
				.set_id(client_id++)
				.build();
			socket.SendTo(add, packet.convertToSend());

			//oczekiwanie na ack od klienta
			add = socket.RecvFrom(buffer.data(), buffer.size());
			packet = Packet::GenerateIdPacketBuilder().build(buffer);
			if (packet.getOperation() != 6) {
				auto id = packet.getId();
				/*  koniec po³¹czenia  */
				packet = Packet::EndPacketBuilder().set_id(id).build();

				socket.SendTo(add, packet.convertToSend());

				continue;
			}

			add = socket.RecvFrom(buffer.data(), buffer.size());
			packet = Packet::GenerateIdPacketBuilder().build(buffer);
			if (packet.getOperation() != 3) {
				auto id = packet.getId();
				/*  koniec po³¹czenia  */
				packet = Packet::EndPacketBuilder().set_id(id).build();

				socket.SendTo(add, packet.convertToSend());

				continue;
			}

			//dodanie liczby L otrzymanej od klienta
			numbersL[0] = packet.getResponse();

		}
	}
	catch (std::system_error& e) {
		std::cout << e.what();
	}
	return 0;
}