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
	- wyj�tki i �apanie wyj�tk�w (zmiana w builderach z exception na w�asny autorski wyj�tek)
	- w�tki - 1 zarz�dzaj�cy - czyli main i 2 dla 2 klient�w
	- klasa klienta

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