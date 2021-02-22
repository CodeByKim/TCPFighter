#pragma once

#include "CommonLibrary.h"
#include "RingBuffer.h"

class Socket
{
public:
	Socket();
	~Socket();

	bool Create();
	bool Create(SOCKET sock, SOCKADDR_IN addr);
	bool Bind(std::string_view, unsigned short port);
	bool Listen();
	bool Connect(std::string_view, unsigned short port);

	int Receive(char* buffer, int size);
	int Send(char* buffer, int size);
	void Close();

	void SetNonblocking();
	SOCKET GetSocketHandle();

private:	
	SOCKET mSocket;
	SOCKADDR_IN mAddr;
};