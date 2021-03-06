#include "Connection.h"
#include "NetPacket.h"

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
	int recvSize = mSocket.Receive(mRecvBuffer.GetBufferRear(), mRecvBuffer.GetDirectEnqueueSize());
	mRecvBuffer.MoveRear(recvSize);	
	return recvSize;
}

void Connection::SendPacket(std::shared_ptr<NetPacket> packet)
{		
	if (!mSendBuffer.Enqueue((char*)&packet->header, PACKET_HEADER_SIZE))
	{
		//sendQueue에 데이터를 못넣었다고?
		//바로 디스커넥트
		mSocket.Close();
	}
	
	//sendQueue에 페이로드 삽입	
	if (!mSendBuffer.Enqueue(packet->GetBuffer(), packet->header.size))
	{
		//sendQueue에 데이터를 못넣었다고?
		//일단 헤더 넣은거 뺴버려야겠네
		
		mSendBuffer.MoveFront(PACKET_HEADER_SIZE);
		mSocket.Close();
	}

	//sendQueue에 있는 모든 데이터 전송해야 함
	while (true)
	{
		//비어있다면 전부 다 보낸거니까 탈출
		if (mSendBuffer.IsEmpty())
		{
			break;
		}
						
		int sendByte = mSocket.Send(mSendBuffer.GetBufferFront(), mSendBuffer.GetDirectDequeueSize());
		mSendBuffer.MoveFront(sendByte);
		
		if (sendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				//어차피 지금 송신큐 꽉차서 못보냄... 나중에 전송해야함
				//일단은 지금은.. 걍 뺑뺑이 돌리자.
				continue;
			}
		}
	}
}

bool Connection::GetPacket(std::queue<std::shared_ptr<NetPacket>>* packetQueue)
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

			std::shared_ptr<NetPacket> packet = std::make_shared<NetPacket>();			
			packet->SetHeader(header);
			packet->SetPayload(buffer + PACKET_HEADER_SIZE, header.size);
			
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