#pragma once
#include "AsynchronousQueue.h"
#include <WinSock2.h>

class Packet;

class Client {
private:
	unsigned short id;
	unsigned short numberL;
	unsigned short numberOfAttempt;
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

	unsigned short getNumberOfAttempt();
public:
	Client(AsynchronousQueue& queue, const unsigned short id);
	~Client() {}

	void run();

	unsigned short getId() const;
	sockaddr_in getAddressStructure() const;
	unsigned short getNumberL() const;

	void setNumberOfAttempt(const unsigned short number);
};

