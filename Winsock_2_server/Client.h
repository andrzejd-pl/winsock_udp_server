#pragma once
#include "UDPSocket.h"

class Packet;

class Client
{
private:
	sockaddr_in add;
	UDPSocket& sock;
public:
	Client(UDPSocket& main_sock, const sockaddr_in& address) : add(address), sock(main_sock) {}
	~Client() {}

	void sendMessage(const Packet& message);
	Packet receiveMessage();
	std::string getAddress();
	std::string getPort();

};

