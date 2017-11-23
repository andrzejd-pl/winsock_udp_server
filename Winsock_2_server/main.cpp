#include <iostream>
#include "WSASession.h"
#include "UDPSocket.h"
#include "Packet.h"
#include <vector>
#include <array>
#include <bitset>

#pragma comment (lib, "Ws2_32.lib")

/*
	TODO:
	- klasy dla ka�dego typu pakiet�w
	- wyj�tki i �apanie wyj�tk�w (zmiana w builderach z exception na w�asny autorski wyj�tek)
	- w�tki - 1 zarz�dzaj�cy - czyli main i 2 dla 2 klient�w
	- klasa klienta
	- klasy builder�w dla brakuj�cych pakiet�w

	Buildery:
		GenerateId - Generowanie id (0 - 0000)
		Expect - Oczekiwanie (1 - 0001)
		Start - Start rozgrywki (2 - 0010)
		Response - przes�anie liczby L (3 - 0011)
		Assay - przes�anie liczby pr�b (4 - 0100)
		Answer - Przes�anie odpowiedzi (5 - 0101)
		CorrectAnswer - Przes�anie komunikatu o wygranej/przegranej/kolejnej pr�bie (6 - 0110)
		Ack - Potwierdzenie przes�ania pakietu (7 - 0111)
		End - Koniec po��czenia (15 - 1111)

*/

int main() {
	try {

		//	/*read address ip sender's*/
		//
		//	char ip[20];
		//	InetNtop(AF_INET, (add.sin_addr.s_addr), ip, 20);
		//
		//	/*-----------------*/

		/*for(const auto t : buffer) {
		std::cout << std::bitset<8>(t) << " ";
		}
		std::cout << std::endl;
		*/
		//	sockaddr_in add = socket.RecvFrom(buffer, 2);

		//	for(const auto t : buffer) {
		//		std::cout << std::bitset<8>(t) << " ";
		//	}
		//	//if (packet.getOperation() != 0) {
		//		/*  koniec po��czenia  */
		//	Packet packet = Packet::EndPacketBuilder().set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());

		//	packet = Packet::AckPacketBuilder().set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());
		//	packet = Packet::CorrectAnswerPacketBuilder().set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());
		//	packet = Packet::ExpectPacketBuilder().set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());
		//	packet = Packet::GenerateIdPacketBuilder().set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());
		//	packet = Packet::StartPacketBuilder().set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());
		//	packet = Packet::AssayPacketBuilder().set_response(5).set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());
		//	packet = Packet::ResponsePacketBuilder().set_response(4).set_id(client_id).build();
		//	socket.SendTo(add, packet.convertToSend());
		//	//continue;
		////}

		//	break;
		//std::array<unsigned short, 2> numbersL;
		WSASession session;
		UDPSocket socket;
		std::vector<char> buffer(2);

		unsigned int client_id = 1;

		socket.Bind(100);
		while(true) {


			sockaddr_in add = socket.RecvFrom(buffer, 2);
			Packet generateId = Packet::GenerateIdPacketBuilder().build(buffer);
			socket.SendTo(add, Packet::AckPacketBuilder().set_id(0).build().convertToSend());

			generateId = Packet::GenerateIdPacketBuilder().set_id(client_id).build();
			socket.SendTo(add, generateId.convertToSend());
			Packet ack = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));

			Packet response = Packet::ResponsePacketBuilder().build(socket.RecvFrom(add, 2));
			socket.SendTo(add, Packet::AckPacketBuilder().set_id(client_id).build().convertToSend());
			short numberL = response.getResponse();

			socket.SendTo(add, Packet::ExpectPacketBuilder().set_id(client_id).build().convertToSend());
			ack = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));

			socket.SendTo(add, Packet::AssayPacketBuilder().set_id(client_id).set_response(numberL / 2).build().convertToSend());
			ack = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));

			numberL /= 2;

			socket.SendTo(add, Packet::StartPacketBuilder().set_id(client_id).build().convertToSend());
			ack = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));

			do {
				
				response = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));
				socket.SendTo(add, Packet::AckPacketBuilder().set_id(client_id).build().convertToSend());

				numberL--;
				std::cout << "Odpowiedz: " << response.getResponse() << std::endl;
				if(response.getResponse() == 5) {
					socket.SendTo(add, Packet::PacketBuilder().set_operation(6).set_response(2).set_id(client_id).build().convertToSend());
					ack = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));
					std::cout << "Wygra�o!!!" << std::endl;
				}
				else if (numberL <= 0) {
					socket.SendTo(add, Packet::PacketBuilder().set_operation(6).set_response(0).set_id(client_id).build().convertToSend());
					ack = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));
					std::cout << "Przegra�o!!!" << std::endl;
				}
				else {
					socket.SendTo(add, Packet::PacketBuilder().set_operation(6).set_response(1).set_id(client_id).build().convertToSend());
					ack = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));
					std::cout << "Dawaj dalej!!!" << std::endl;
				}
			} while(response.getResponse() != 5 && numberL > 0);

			Packet end = Packet::PacketBuilder().build(socket.RecvFrom(add, 2));
			socket.SendTo(add, Packet::AckPacketBuilder().set_id(client_id).build().convertToSend());

			std::cout << "Koniec!!!" << std::endl;
		}
	}
	catch(const std::system_error& e) {
		std::cout << e.what();
	}
	return 0;
}