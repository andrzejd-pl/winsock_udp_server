#pragma once
#include "UDPSocket.h"
#include "Packet.h"

class Packet;

class Client {
private:
	const unsigned short buffer_size = 2;
	const unsigned short default_id = 0;
	sockaddr_in add;
	UDPSocket& sock;
	unsigned short id;
public:
	Client(UDPSocket& main_sock, const unsigned short id);
	~Client() {}

	void sendMessage(Packet::PacketBuilder message);
	void sendAckMessage();

	Packet receiveMessage();
	Packet receiveAckMessage();

	std::vector<char> getAddress();
	std::string getPort() const;
};

