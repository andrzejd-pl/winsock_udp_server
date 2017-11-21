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

Packet::Packet(const std::vector<char>& rawData)
{
	if (rawData.size() > 2) throw std::exception("To large buffor!!!");

	unsigned short buff = rawData[0];
	operation = 0 | ((buff >> 4) & 0x0F);
	response = 0 | ((buff >> 1) & 0x07);
	id = 0 | ((buff & 0x01) << 3);

	buff = rawData[1];
	id |= ((buff >> 5) & 0x07);
}

Packet Packet::PacketBuilder::build(const char* data, const unsigned short size) {
	return Packet(data, size);
}

Packet::AckPacketBuilder::AckPacketBuilder() : PacketBuilder() {
	operation = 6;
	response = 0;
}

Packet::PacketBuilder Packet::AckPacketBuilder::set_operation(const unsigned short operation) {
	return *this;
}

Packet::PacketBuilder Packet::AckPacketBuilder::set_response(const unsigned short response) {
	return *this;
}

Packet Packet::AckPacketBuilder::build(const std::string& data) {
	Packet rt(data.data(), data.size());
	if (rt.getOperation() != 6 || rt.getResponse() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet Packet::AckPacketBuilder::build(const std::vector<char>& data) {
	Packet rt(data.data(), data.size());
	if (rt.getOperation() != 6 || rt.getResponse() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet Packet::AckPacketBuilder::build(const char* data, const unsigned short size) {
	Packet rt(data, size);
	if (rt.getOperation() != 6 || rt.getResponse() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet::GenerateIdPacketBuilder::GenerateIdPacketBuilder() : PacketBuilder() {
	operation = 0;
	response = 0;
}

Packet::PacketBuilder Packet::GenerateIdPacketBuilder::set_operation(const unsigned short operation) {
	return *this;
}

Packet::PacketBuilder Packet::GenerateIdPacketBuilder::set_response(const unsigned short response) {
	return *this;
}

Packet Packet::GenerateIdPacketBuilder::build(const std::string& data) {
	Packet rt(data.data(), data.size());
	if (rt.getOperation() != 0 || rt.getResponse() != 0 || rt.getId() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet Packet::GenerateIdPacketBuilder::build(const std::vector<char>& data) {
	Packet rt(data);
	if (rt.getOperation() != 0 || rt.getResponse() != 0 || rt.getId() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet Packet::GenerateIdPacketBuilder::build(const char* data, const unsigned short size) {
	Packet rt(data, size);
	if (rt.getOperation() != 0 || rt.getResponse() != 0 || rt.getId() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet::StartPacketBuilder::StartPacketBuilder() : PacketBuilder() {
	operation = 2;
	response = 0;
}

Packet::PacketBuilder Packet::StartPacketBuilder::set_operation(const unsigned short operation) {
	return *this;
}

Packet::PacketBuilder Packet::StartPacketBuilder::set_response(const unsigned short response) {
	return *this;
}

Packet::CorrectAnswerPacketBuilder::CorrectAnswerPacketBuilder() : PacketBuilder() {
	operation = 5;
}

Packet::PacketBuilder Packet::CorrectAnswerPacketBuilder::set_operation(const unsigned short operation) {
	return *this;
}

Packet::EndPacketBuilder::EndPacketBuilder() : PacketBuilder() {
	operation = 15;
	response = 0;
}

Packet::PacketBuilder Packet::EndPacketBuilder::set_operation(const unsigned short operation) {
	return *this;
}

Packet::PacketBuilder Packet::EndPacketBuilder::set_response(const unsigned short response) {
	return *this;
}

Packet Packet::EndPacketBuilder::build(const std::string& data)
{
	Packet rt(data.data(), data.size());
	if (rt.getOperation() != 15 || rt.getResponse() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet Packet::EndPacketBuilder::build(const std::vector<char>& data)
{
	Packet rt(data.data(), data.size());
	if (rt.getOperation() != 15 || rt.getResponse() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
}

Packet Packet::EndPacketBuilder::build(const char* data, const unsigned short size)
{
	Packet rt(data, size);
	if (rt.getOperation() != 15 || rt.getResponse() != 0)
		throw std::exception("Invalid packet!!!!"); // poprawi� na lepsze
	return rt;
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

Packet Packet::PacketBuilder::build() {
	return Packet(operation, response, id);
}

Packet Packet::PacketBuilder::build(const std::string& data) {
	return Packet(data.data(), data.size());
}

Packet Packet::PacketBuilder::build(const std::vector<char>& data) {
	return Packet(data.data(), data.size());
}

Packet::ExpectPacketBuilder::ExpectPacketBuilder() : PacketBuilder() {
	operation = 1;
	response = 0;
}

Packet::PacketBuilder Packet::ExpectPacketBuilder::set_operation(const unsigned short operation) {
	return *this;
}

Packet::PacketBuilder Packet::ExpectPacketBuilder::set_response(const unsigned short response) {
	return *this;
}
