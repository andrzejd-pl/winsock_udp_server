#pragma once
#include "AsynchronousQueue.h"
#include <WinSock2.h>

class Packet;

class Client {
private:
	unsigned short id;
	AsynchronousQueue& queue;
	sockaddr_in addr;

	void generateId(const Packet& packet);
	void expect(const Packet& packet);
	void start(const Packet& packet);
	void response(const Packet& packet);
	void assay(const Packet& packet);
	void answer(const Packet& packet);
	void correctAnswer(const Packet& packet);
	void ack(const Packet& packet);
	void end(const Packet& packet);
public:
	Client(AsynchronousQueue& queue, const unsigned short id);
	~Client() {}

	void run();

	unsigned short getId() const;
	sockaddr_in getAddressStructure() const;
};

