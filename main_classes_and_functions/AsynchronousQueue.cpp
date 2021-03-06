#include "AsynchronousQueue.h"

AsynchronousQueue::AsynchronousQueue() {}

Packet AsynchronousQueue::popReceivedPacket() {
	std::lock_guard<std::mutex> lock(receivedMutex);
	Packet rt = receivedPackets.front();
	receivedPackets.pop();
	return rt;
}

Packet AsynchronousQueue::popSendPacket() {
	sendMutex.lock();
	Packet rt = sendPackets.front();
	sendPackets.pop();
	sendMutex.unlock();

	return rt;
}

void AsynchronousQueue::pushReceivedPacket(const Packet& packet) {
	receivedMutex.lock();
	receivedPackets.push(packet);
	receivedMutex.unlock();
}

void AsynchronousQueue::pushSendPacket(const Packet& packet) {
	while(!receivedPackets.empty()); // TODO: to poprawi�
	sendMutex.lock();
	sendPackets.push(packet);
	sendMutex.unlock();
}



AsynchronousQueue::~AsynchronousQueue() {}
