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
BOOST_AUTO_TEST_SUITE_END();