#pragma once
#include <queue>
#include <mutex>
#include "../network_library/Packet.h"

class AsynchronousQueue {
private:
	std::queue<Packet> receivedPackets;
	std::queue<Packet> sendPackets;

	std::mutex sendMutex;
	std::mutex receivedMutex;

	std::condition_variable sendCv;
	std::condition_variable receivedCv;

	bool sendReady = false;
	bool receivedReady = false;
public:
	AsynchronousQueue();

	Packet popReceivedPacket();
	Packet popSendPacket();

	void pushReceivedPacket(const Packet& packet);
	void pushSendPacket(const Packet& packet);

	~AsynchronousQueue();
};
