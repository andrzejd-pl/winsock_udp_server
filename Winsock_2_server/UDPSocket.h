#include <WinSock2.h>
#include <string>
#include <vector>

#pragma comment (lib, "Ws2_32.lib")
#pragma once

class UDPSocket
{
private:
	SOCKET sock;
public:
	UDPSocket();
	~UDPSocket();

	void SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int  flags = 0);
	void SendTo(const std::string& address, unsigned short port, const std::vector<char>& buffer, int  flags = 0);
	void SendTo(const std::string& address, unsigned short port, const std::string& buffer, int  flags = 0);

	void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0);
	void SendTo(sockaddr_in& address, const std::vector<char>& buffer, int flags = 0);
	void SendTo(sockaddr_in& address, const std::string& buffer, int flags = 0);
	sockaddr_in RecvFrom(char* buffer, int len, int flags = 0);
	void Bind(unsigned short port);
};

