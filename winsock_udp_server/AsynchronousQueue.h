#pragma once
#include <queue>
#include "Packet.h"
#include <mutex>

class AsynchronousQueue {
private:
	std::queue<Packet> receivedPackets;
	std::queue<Packet> sendPackets;

	std::mutex sendMutex;
	std::mutex receivedMutex;
public:
	AsynchronousQueue();

	Packet popReceivedPacket();
	Packet popSendPacket();

	void pushReceivedPacket(const Packet& packet);
	void pushSendPacket(const Packet& packet);

	~AsynchronousQueue();
};
