#define BOOST_TEST_MODULE NetLibTest
#include <boost/test/included/unit_test.hpp>
//#include "../network_library/UDPSocket.h"
#include "../network_library/Packet.h"

BOOST_AUTO_TEST_SUITE(PacketTest);
BOOST_AUTO_TEST_CASE(Simple_Builder) {
	int operation = 1, id = 1, response = 1;
	Packet p = Packet::PacketBuilder().
		set_operation(operation).
		set_id(id).
		set_response(response).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(ExpectBuilder) {
	int operation = 1, id = 1, response = 0;
	Packet p = Packet::ExpectPacketBuilder().
		set_id(1).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(AckBuilder) {
	int operation = 7, id = 1, response = 0;
	Packet p = Packet::AckPacketBuilder().
		set_id(id).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(AnswerBuilder) {
	int operation = 5, id = 1, response = 7;
	Packet p = Packet::AnswerPacketBuilder().
		set_id(id).
		set_response(response).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(GenerateIdBuilder) {
	int operation = 0, id = 1, response = 0;
	Packet p = Packet::GenerateIdPacketBuilder().
		set_id(id).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(StartBuilder) {
	int operation = 2, id = 1, response = 0;
	Packet p = Packet::StartPacketBuilder().
		set_id(id).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(CorrectAnswerBuilder) {
	int operation = 6, id = 1, response = 2;
	Packet p = Packet::CorrectAnswerPacketBuilder().
		set_id(id).
		set_response(response).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(EndBuilder) {
	int operation = 15, id = 1, response = 0;
	Packet p = Packet::EndPacketBuilder().
		set_id(id).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(ResponseBuilder) {
	int operation = 3, id = 1, response = 5;
	Packet p = Packet::ResponsePacketBuilder().
		set_id(id).
		set_response(response).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_CASE(AssayBuilder) {
	int operation = 4, id = 1, response = 4;
	Packet p = Packet::AssayPacketBuilder().
		set_id(id).
		set_response(response).
		build();

	std::string buff;
	char element = 0;
	element |= (operation << 4);
	element |= (response << 1);
	element |= (id >> 3);
	buff.push_back(element);

	element = 0;
	element |= (id << 5);
	buff.push_back(element);

	BOOST_TEST(p.convertToSend() == buff);
}
BOOST_AUTO_TEST_SUITE_END();