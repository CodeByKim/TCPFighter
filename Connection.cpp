#include "Connection.h"
#include "Packet.h"

Connection::Connection()
	: mRecvBuffer(RING_BUFFER_SIZE)
	, mSendBuffer(RING_BUFFER_SIZE)
{		
	
}

Connection::~Connection()
{	
	Release();
}

void Connection::Initialize()
{
	if (!mSocket.Create())
	{
		MessageBox(NULL, L"Create Socket Error", L"Error", 0);
	}
}

void Connection::Initialize(SOCKET sock, SOCKADDR_IN addr)
{
	if (!mSocket.Create(sock, addr))
	{		
		MessageBox(NULL, L"Create Socket Error", L"Error", 0);
	}
}

void Connection::Release()
{
	mSocket.Close();
}

bool Connection::Connect(std::string_view ip, unsigned short port)
{
	return mSocket.Connect(ip, port);
}

int Connection::Receive()
{
	char buffer[BUFFER_SIZE];
	int recvSize = mSocket.Receive(buffer, BUFFER_SIZE);
	mRecvBuffer.Enqueue(buffer, recvSize);

	return recvSize;
}

void Connection::SendPacket(std::shared_ptr<Packet> packet)
{	
	//sendQueue에 넣는작업 필요...
	//근데 일단 그냥 되는지 테스트도 해보자.
	//mSocket.Send(packet->data, packet->header.size + PACKET_HEADER_SIZE);
	mSocket.Send(packet->stream->GetBuffer(), packet->header.size + PACKET_HEADER_SIZE);
}

bool Connection::GetPacket(std::queue<std::shared_ptr<Packet>>* packetQueue)
{	
	while (true)
	{
		char buffer[BUFFER_SIZE];		
				
		if (mRecvBuffer.Peek(buffer, PACKET_HEADER_SIZE))
		{						
			PacketHeader header;
			CopyMemory(&header, buffer, PACKET_HEADER_SIZE);
			
			if (!mRecvBuffer.Peek(buffer, header.size + PACKET_HEADER_SIZE))
			{
				break;
			}

			mRecvBuffer.MoveFront(PACKET_HEADER_SIZE + header.size);

			std::shared_ptr<Packet> packet = std::make_shared<Packet>();
			packet->header = header;
			packet->SetMemoryStream(buffer + PACKET_HEADER_SIZE, header.size);
			//packet->data = new char[header.size];
			//CopyMemory(packet->data, buffer + PACKET_HEADER_SIZE, header.size);
			packetQueue->push(packet);
		}
		else
		{
			break;
		}
	}

	return packetQueue->size() > 0;
}

SOCKET Connection::GetSocketHandle()
{
	return mSocket.GetSocketHandle();
}