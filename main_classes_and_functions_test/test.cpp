#define BOOST_TEST_MODULE MainLibTest
#include <boost/test/included/unit_test.hpp>
#include "../main_classes_and_functions/AsynchronousQueue.h"

std::vector<Packet> generateVectorPackets(unsigned int n) {
	std::vector<Packet> packets((n > 0) ? generateVectorPackets(n - 1) : std::vector<Packet>());
	packets.push_back(Packet::PacketBuilder().set_operation(n).set_id(n + 1).set_response(n + 2).build());
	return packets;
}

BOOST_FIXTURE_TEST_SUITE(AsyncQueueTest, AsynchronousQueue)
BOOST_AUTO_TEST_CASE(sendQueueTest) {
	std::vector<Packet> packets = generateVectorPackets(5);

	for (auto packet : packets) {
		this->pushSendPacket(packet);
	}

	for (auto packet : packets) {
		BOOST_CHECK(this->popSendPacket() == packet);
	}
}
BOOST_AUTO_TEST_CASE(recvQueueTest) {
	std::vector<Packet> packets;

	for (auto packet : packets) {
		this->pushReceivedPacket(packet);
	}

	for (auto packet : packets) {
		BOOST_CHECK(this->popReceivedPacket() == packet);
	}
}
BOOST_AUTO_TEST_SUITE_END()