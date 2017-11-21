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
	- klasy builder�w dla brakuj�cych pakiet�w 

	Buildery:
		End - Koniec po��czenia (15 - 1111)
		Ack - Potwierdzenie przes�ania pakietu (6 - 0110)
		CorrectAnswer - Przes�anie komunikatu o wygranej/przegranej/kolejnej pr�bie (5 - 0101)
		Expect - Oczekiwanie (1 - 0001)
		GenerateId - Generowanie id (0 - 0000)
		Start - Start rozgrywki (2 - 0010)
		brakuje:
		przes�anie liczby L (3 - 0011)
		przes�anie liczby pr�b (4 - 0100)
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
			sockaddr_in add = socket.RecvFrom(buffer, 2);

			Packet packet = Packet::GenerateIdPacketBuilder().build(buffer);

			//if (packet.getOperation() != 0) {
				/*  koniec po��czenia  */
				packet = Packet::EndPacketBuilder().set_id(1).build();
				socket.SendTo(add, packet.convertToSend());

				packet = Packet::AckPacketBuilder().set_id(1).build();
				socket.SendTo(add, packet.convertToSend());
				packet = Packet::CorrectAnswerPacketBuilder().set_id(1).build();
				socket.SendTo(add, packet.convertToSend());
				packet = Packet::ExpectPacketBuilder().set_id(1).build();
				socket.SendTo(add, packet.convertToSend());
				packet = Packet::GenerateIdPacketBuilder().set_id(1).build();
				socket.SendTo(add, packet.convertToSend());
				packet = Packet::StartPacketBuilder().set_id(1).build();
				socket.SendTo(add, packet.convertToSend());
				//continue;
			//}

				break;


		}
	}
	catch (std::system_error& e) {
		std::cout << e.what();
	}
	return 0;
}