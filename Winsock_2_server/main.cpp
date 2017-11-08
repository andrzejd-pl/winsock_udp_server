#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "WSASession.h"
#include "UDPSocket.h"



void sock(bool &stop) {
	WSASession Session;
	UDPSocket Socket;

	Socket.Bind(100);

	char buffer[100];

	while (!stop) {
		sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));

		std::string input(buffer);
		std::reverse(std::begin(input), std::end(input));
		Socket.SendTo(add, input.c_str(), input.size());
	}
}

int main() {
	try {
		bool stop_thread = false;
		std::thread sock(sock, std::ref(stop_thread));

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		stop_thread = true;
		sock.join();
	}
	catch (std::system_error& e) {
		std::cout << e.what();
	}

	return 0;
}