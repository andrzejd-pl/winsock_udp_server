#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "WSASession.h"
#include "UDPSocket.h"
#include "Packet.h"
#include <vector>
#include "Client.h"
#include <thread>
#include <mutex>

#pragma comment (lib, "Ws2_32.lib")

/*
	TODO:
	- wyj¹tki i ³apanie wyj¹tków (zmiana w builderach z exception na w³asny autorski wyj¹tek)
	- w¹tki - 1 zarz¹dzaj¹cy - czyli main i 2 dla 2 klientów
	- klasa klienta

	Buildery:
	GenerateId - Generowanie id (0 - 0000)
	Expect - Oczekiwanie (1 - 0001)
	Start - Start rozgrywki (2 - 0010)
	Response - przes³anie liczby L (3 - 0011)
	Assay - przes³anie liczby prób (4 - 0100)
	Answer - Przes³anie odpowiedzi (5 - 0101)
	CorrectAnswer - Przes³anie komunikatu o wygranej/przegranej/kolejnej próbie (6 - 0110)
	Ack - Potwierdzenie przes³ania pakietu (7 - 0111)
	End - Koniec po³¹czenia (15 - 1111)

*/

int main() {
	try {
		WSASession Session;
		UDPSocket Socket;
		char buffer[100];

		Socket.Bind(100);
		while (1) {
			sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));



			std::string input(buffer);
			std::reverse(std::begin(input), std::end(input));
			Socket.SendTo(add, input.c_str(), input.size());

		}
	}
	catch(const std::system_error& e) {
		std::cout << e.what();
	}

	return 0;
}