#pragma once
#include <string>

/*
	TODO: 
	1) walidowaæ pola struktury
	2) ...
*/

struct Packet {
private:
	unsigned short operation;
	unsigned short response;
	unsigned short id;
	unsigned short ack;
	unsigned short error;
	unsigned short overflow;
	unsigned short bad_respone;
	unsigned short bad_client;
	Packet(const unsigned short _opr, const unsigned short _ret, const unsigned short _id, const bool _ack, const bool _error, const bool _overflow, const bool _bad_response, const bool _bad_client);
	Packet() {}

public:
	Packet(const char* rawData, const unsigned short size);

	std::string convertToSend() const;

	unsigned short getOperation() const;
	unsigned short getResponse() const;
	unsigned short getId() const;

	class PacketBuilder {
	private:
		unsigned short operation;
		unsigned short response;
		unsigned short id;
		unsigned short ack;
		unsigned short error;
		unsigned short overflow;
		unsigned short bad_respone;
		unsigned short bad_client;
	public:

		PacketBuilder set_operation(const unsigned short operation);
		PacketBuilder set_response(const unsigned short response);
		PacketBuilder set_id(const unsigned short id);
		PacketBuilder set_ack(const unsigned short ack);
		PacketBuilder set_error(const unsigned short error);
		PacketBuilder set_overflow(const unsigned short overflow);
		PacketBuilder set_bad_respone(const unsigned short bad_respone);
		PacketBuilder set_bad_client(const unsigned short bad_client);

		Packet build();
	};
};

