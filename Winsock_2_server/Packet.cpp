#include "Packet.h"

Packet::Packet(const char* rawData, const unsigned short size) {
	if (size > 2) throw std::exception("To large buffor!!!");

	unsigned short buff = rawData[0];
	operation = 0 | ((buff >> 4) & 0x0F);
	response = 0 | ((buff >> 1) & 0x07);
	id = 0 | ((buff & 0x01) << 3);

	buff = rawData[1];
	id |= ((buff >> 5) & 0x07);
}

std::string Packet::convertToSend() const {
	std::string rt;
	char buff = 0;

	buff |= (operation << 4);
	buff |= (response << 1);
	buff |= (id >> 3);
	rt.push_back(buff);

	buff = 0;
	buff |= (id << 5);
	buff |= (0x0F);
	rt.push_back(buff);

	return rt;
}

unsigned short Packet::getOperation() const {
	return operation;
}

unsigned short Packet::getResponse() const {
	return response;
}

unsigned short Packet::getId() const {
	return id;
}

Packet::PacketBuilder Packet::PacketBuilder::set_operation(const unsigned short operation) {
	this->operation = operation;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_response(const unsigned short response) {
	this->response = response;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_id(const unsigned short id) {
	this->id = id;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_ack(const unsigned short ack) {
	this->ack = ack;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_error(const unsigned short error) {
	this->error = error;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_overflow(const unsigned short overflow) {
	this->overflow = overflow;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_bad_respone(const unsigned short bad_respone) {
	this->bad_respone = bad_respone;
	return *this;
}

Packet::PacketBuilder Packet::PacketBuilder::set_bad_client(const unsigned short bad_client) {
	this->bad_client = bad_client;
	return *this;
}

Packet Packet::PacketBuilder::build() {
	return Packet(operation, response, id, ack, error, overflow, response, bad_client);

}