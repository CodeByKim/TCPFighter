#pragma once

#include "CommonLibrary.h"
#include "Socket.h"

class NetPacket;

class Connection
{
public:
	Connection();
	~Connection();

	void Initialize();
	void Initialize(SOCKET sock, SOCKADDR_IN addr);
	void Release();

	bool Connect(std::string_view ip, unsigned short port);
	int Receive();	
	void SendPacket(std::shared_ptr<NetPacket> packet);
	bool GetPacket(std::queue<std::shared_ptr<NetPacket>>* packetQueue);

	SOCKET GetSocketHandle();

private:
	RingBuffer mRecvBuffer;
	RingBuffer mSendBuffer;

	Socket mSocket;
};