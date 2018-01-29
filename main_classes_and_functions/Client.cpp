#include "Client.h"
#include <random>

#pragma comment (lib, "Ws2_32.lib")

int randomInt(int min, int max) {
	static std::random_device rd;
	std::uniform_int_distribution<int> d(min, max);
	return d(rd);
}

void Client::generateId(const Packet& packet) {
	queue.pushSendPacket(Packet::AckPacketBuilder().set_id(0).build());
	id = randomInt(0, 15); // TODO: poprawi� aby wyklucza� u�yte ju� id
	queue.pushSendPacket(Packet::GenerateIdPacketBuilder().set_id(id).build());
}

void Client::expect(const Packet& packet) { 
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}

void Client::start(const Packet& packet) {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}

void Client::response(const Packet& packet) {
	numberL = packet.getResponse();
	queue.pushSendPacket(Packet::AckPacketBuilder().set_id(id).build());
}

void Client::assay(const Packet& packet) {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}

void Client::answer(const Packet& packet) {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}


void Client::correctAnswer(const Packet& packet) {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}

void Client::ack(const Packet& packet) {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}

void Client::end(const Packet& packet) {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}

unsigned short Client::getNumberOfAttempt() {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
	return 0;
}

Client::Client(AsynchronousQueue& queue, const unsigned short id) : id(id), queue(queue) {}

void Client::run() {
	while(true) {
		Packet receivePacket = queue.popReceivedPacket();
		switch(receivePacket.getOperation()) {
			case 0:
				{
					generateId(receivePacket);
					break;
				}
			case 3:
				{
					response(receivePacket);
					break;
				}
			case 4:
				{
					assay(receivePacket);
					break;
				}
			case 5:
				{
					answer(receivePacket);
					break;
				}
			case 6:
				{
					correctAnswer(receivePacket);
					break;
				}
			case 15:
				{
					end(receivePacket);
					break;
				}
		}
	}
}

unsigned short Client::getId() const {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
	return 0;
}

sockaddr_in Client::getAddressStructure() const {
	return addr;
}

unsigned short Client::getNumberL() const {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
	return 0;
}

void Client::setNumberOfAttempt(const unsigned short number) {
	//TODO: napisa� metod� przetwarzaj�c� pakiet
}
