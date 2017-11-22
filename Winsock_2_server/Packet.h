#pragma once
#include <vector>

class Packet {
private:
	unsigned short operation;
	unsigned short response;
	unsigned short id;


	Packet(const unsigned short operation, const unsigned short response, const unsigned short id)
		: operation(operation),
		response(response),
		id(id) {}

	Packet() : operation(0), response(0), id(0) {}

	Packet(const char* rawData, const unsigned short size);
	Packet(const std::vector<char>& rawData);
public:

	std::string convertToSend() const;

	unsigned short getOperation() const;
	unsigned short getResponse() const;
	unsigned short getId() const;

	class PacketBuilder {
	protected:
		unsigned short operation;
		unsigned short response;
		unsigned short id;
	public:
		PacketBuilder() : operation(), response(), id() {}


		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);
		virtual PacketBuilder set_id(const unsigned short id);

		Packet build();
		virtual Packet build(const std::string& data);
		virtual Packet build(const std::vector<char>& data);
		virtual Packet build(const char* data, const unsigned short size);

		virtual ~PacketBuilder() {}
	};

	class ExpectPacketBuilder : public PacketBuilder {
	public:
		ExpectPacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);
	};

	class AckPacketBuilder : public PacketBuilder {
	public:
		AckPacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);


		virtual Packet build(const std::string& data);
		virtual Packet build(const std::vector<char>& data);
		virtual Packet build(const char* data, const unsigned short size);

	};

	class GenerateIdPacketBuilder : public PacketBuilder {
	public:
		GenerateIdPacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);

		virtual Packet build(const std::string& data);
		virtual Packet build(const std::vector<char>& data);
		virtual Packet build(const char* data, const unsigned short size);
	};

	class StartPacketBuilder : public PacketBuilder {
	public:
		StartPacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);
	};

	class CorrectAnswerPacketBuilder : public PacketBuilder {
	public:
		CorrectAnswerPacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
	};

	class EndPacketBuilder : public PacketBuilder {
	public:
		EndPacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);

		virtual Packet build(const std::string& data);
		virtual Packet build(const std::vector<char>& data);
		virtual Packet build(const char* data, const unsigned short size);
	};

	class ResponsePacketBuilder : public PacketBuilder {
	public:
		ResponsePacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);

		virtual Packet build(const std::string& data);
		virtual Packet build(const std::vector<char>& data);
		virtual Packet build(const char* data, const unsigned short size);
	};

	class AssayPacketBuilder : public PacketBuilder {
	public:
		AssayPacketBuilder();

		virtual PacketBuilder set_operation(const unsigned short operation);
		virtual PacketBuilder set_response(const unsigned short response);

		virtual Packet build(const std::string& data);
		virtual Packet build(const std::vector<char>& data);
		virtual Packet build(const char* data, const unsigned short size);
	};


};

