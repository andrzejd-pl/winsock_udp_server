#include "AsynchronousQueue.h"



AsynchronousQueue::AsynchronousQueue() {}

Packet AsynchronousQueue::popReceivedPacket() {
	receivedMutex.lock();
	Packet rt = receivedPackets.front();
	receivedMutex.unlock();

	return rt;
}

Packet AsynchronousQueue::popSendPacket() {
	sendMutex.lock();
	Packet rt = sendPackets.front();
	sendMutex.unlock();

	return rt;
}

void AsynchronousQueue::pushReceivedPacket(const Packet& packet) {
	while(!receivedPackets.empty()); // TODO: to poprawiæ
	receivedMutex.lock();
	receivedPackets.push(packet);
	receivedMutex.unlock();
}

void AsynchronousQueue::pushSendPacket(const Packet& packet) {
	while(!receivedPackets.empty()); // TODO: to poprawiæ
	sendMutex.lock();
	sendPackets.push(packet);
	sendMutex.unlock();
}



AsynchronousQueue::~AsynchronousQueue() {}
