#pragma once

#include "CommonLibrary.h"
#include "Socket.h"

class Packet;

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
	void SendPacket(std::shared_ptr<Packet> packet);
	bool GetPacket(std::queue<std::shared_ptr<Packet>>* packetQueue);

	SOCKET GetSocketHandle();

private:
	RingBuffer mRecvBuffer;
	RingBuffer mSendBuffer;

	Socket mSocket;
};