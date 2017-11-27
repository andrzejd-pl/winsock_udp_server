#include "Client.h"
#include "Packet.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

Client::Client(UDPSocket& main_sock, const unsigned short id) : add(), sock(main_sock), id(default_id) {
	std::vector<char> buffer;
	add = sock.RecvFrom(buffer, buffer_size);
	Packet generateId = Packet::GenerateIdPacketBuilder().build(buffer);
	sendAckMessage();

	this->id = id;
	sendMessage(Packet::GenerateIdPacketBuilder());
	Packet ack = receiveMessage();
}

void Client::sendMessage(Packet::PacketBuilder message) {
	sock.SendTo(add, message.set_id(id).build().convertToSend());
}

Packet Client::receiveMessage() {
	return Packet::PacketBuilder().build(sock.RecvFrom(add, buffer_size));
}

Packet Client::receiveAckMessage() {
	return Packet::PacketBuilder().build(sock.RecvFrom(add, buffer_size));
}

std::vector<char> Client::getAddress() {
	std::vector<char> ip(20);
	InetNtop(AF_INET, reinterpret_cast<void *>(&add.sin_addr.s_addr), ip.data(), ip.size());
	return ip;
}

std::string Client::getPort() const {
	unsigned short port = htons(add.sin_port);
	return std::to_string(port);
}

void Client::run() {
	Packet response = this->receiveMessage();
	this->sendAckMessage();
	short numberL = response.getResponse();

	this->sendMessage(Packet::ExpectPacketBuilder());
	Packet ack = this->receiveAckMessage();

	numberL /= 2;

	this->sendMessage(Packet::AssayPacketBuilder().set_response(numberL));
	ack = this->receiveAckMessage();

	this->sendMessage(Packet::StartPacketBuilder());
	ack = this->receiveAckMessage();

	do {

		response = this->receiveMessage();
		this->sendAckMessage();

		numberL--;


		if(response.getResponse() == 5) {
			this->sendMessage(Packet::PacketBuilder().set_operation(6).set_response(2));
			ack = this->receiveAckMessage();
		}
		else if(numberL <= 0) {
			this->sendMessage(Packet::PacketBuilder().set_operation(6).set_response(0));
			ack = this->receiveAckMessage();
		}
		else {
			this->sendMessage(Packet::PacketBuilder().set_operation(6).set_response(1));
			ack = this->receiveAckMessage();
		}
	} while(response.getResponse() != 5 && numberL > 0);

	Packet end = this->receiveMessage();
	this->sendAckMessage();

}

void Client::sendAckMessage() {
	sendMessage(Packet::AckPacketBuilder());
}
