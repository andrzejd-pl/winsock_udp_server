#include <iostream>
#include "../network_library/WSASession.h"
#include "../network_library/UDPSocket.h"
#include "../network_library/Packet.h"
#include <vector>
#include "../main_classes_and_functions/Client.h"

#pragma comment (lib, "Ws2_32.lib")

/*
	TODO:
	- wyj¹tki i ³apanie wyj¹tków (zmiana w builderach z exception na w³asny autorski wyj¹tek)
	- w¹tki - 1 zarz¹dzaj¹cy - czyli main i 2 dla 2 klientów
	- klasa klienta
	- poprawiæ w AsynchronousQueue oczekiwanie na nowy produkt
	- 

	pole: OOOO RRRI IIIU UUUU
	o - bity operacji
	r - bity odpowiedzi
	i - bity id
	u - bity uzupe³nienia


	Buildery pakietów ([S - pakiet wysy³any przez serwer, K- pakiet wysy³any przez klienta]):
	GenerateId - Generowanie id (0 - 0000) [K, S]
	Expect - Oczekiwanie (1 - 0001) [S]
	Start - Start rozgrywki (2 - 0010) [S]
	Response - przes³anie liczby L (3 - 0011) [K]
	Assay - przes³anie liczby prób (4 - 0100) [S]
	Answer - Przes³anie odpowiedzi (5 - 0101) [K]
	CorrectAnswer - Przes³anie komunikatu o wygranej/przegranej/kolejnej próbie (6 - 0110) [S]
	Ack - Potwierdzenie przes³ania pakietu (7 - 0111) [K, S]
	End - Koniec po³¹czenia (15 - 1111) [K, S]

*/

int main() {
	/*try {

		WSASession session;
		UDPSocket socket;
		std::vector<char> buffer(2);

		unsigned int client_id = 1;

		socket.Bind(100);
		while(true) {
			Client client(socket, client_id++);
			Packet response = client.receiveMessage();
			client.sendAckMessage();
			short numberL = response.getResponse();

			client.sendMessage(Packet::ExpectPacketBuilder());
			Packet ack = client.receiveAckMessage();

			numberL /= 2;

			client.sendMessage(Packet::AssayPacketBuilder().set_response(numberL));
			ack = client.receiveAckMessage();

			client.sendMessage(Packet::StartPacketBuilder());
			ack = client.receiveAckMessage();

			do {
				
				response = client.receiveMessage();
				client.sendAckMessage();

				numberL--;


				if(response.getResponse() == 5) {
					client.sendMessage(Packet::PacketBuilder().set_operation(6).set_response(2));
					ack = client.receiveAckMessage();
				}
				else if (numberL <= 0) {
					client.sendMessage(Packet::PacketBuilder().set_operation(6).set_response(0));
					ack = client.receiveAckMessage();
				}
				else {
					client.sendMessage(Packet::PacketBuilder().set_operation(6).set_response(1));
					ack = client.receiveAckMessage();
				}
			} while(response.getResponse() != 5 && numberL > 0);

			Packet end = client.receiveMessage();
			client.sendAckMessage();

		}
	}
	catch(const std::system_error& e) {
		std::cout << e.what();
	}*/
	return 0;
}