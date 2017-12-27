#include "stdafx.h"
#include "CppUnitTest.h"
#include "../winsock_udp_server/AsynchronousQueue.h"
#include "../winsock_udp_server/Packet.h"

template<> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Packet>(const Packet& t) { 
	std::wstringstream _s;
	_s << t.ToString().c_str();
	return _s.str();
}

template<> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Packet>(const Packet* t) {
	std::wstringstream _s;
	_s << t->ToString().c_str();
	return _s.str();
}

template<> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Packet>(Packet* t) {
	std::wstringstream _s;
	_s << t->ToString().c_str();
	return _s.str();
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {
	TEST_CLASS(AsynchronousQueueTest) {
public:

	TEST_METHOD(pushReceivedPacketTest) {
		Packet testPacket = Packet::PacketBuilder().set_id(1).set_operation(0).set_response(6).build();
		AsynchronousQueue queue;

		queue.pushReceivedPacket(testPacket);
		Packet receivedPacket = queue.popReceivedPacket();

		//Assert::AreEqual(testPacket, receivedPacket);
	}

	};
}