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
	if (!mSendBuffer.Enqueue((char*)&packet->header, PACKET_HEADER_SIZE))
	{
		//sendQueue에 데이터를 못넣었다고?
		//바로 디스커넥트
		mSocket.Close();
	}
	
	//sendQueue에 페이로드 삽입
	if (!mSendBuffer.Enqueue(packet->stream->GetBuffer(), packet->header.size))
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
		
		char buffer[1024];
		int useSize = mSendBuffer.GetUseSize();

		if (mSendBuffer.Peek(buffer, useSize))
		{
			int sendByte = mSocket.Send(buffer, useSize);
			if (sendByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					//어차피 지금 송신큐 꽉차서 못보냄... 나중에 전송해야함
					//일단은 지금은.. 걍 뺑뺑이 돌리자.
					continue;
				}
			}

			if (useSize - sendByte > 0)
			{
				int remainByte = useSize - sendByte;
				mSendBuffer.MoveFront(sendByte);
				mSendBuffer.Enqueue(buffer + sendByte, remainByte);
			}
			else
			{
				mSendBuffer.MoveFront(useSize);
			}			
		}		
		else
		{
			//에러인건데...
		}
	}

	//이전 잘 작동했던 코드
	/*char buffer[1024];
	CopyMemory(buffer, &packet->header, PACKET_HEADER_SIZE);
	CopyMemory(buffer+ PACKET_HEADER_SIZE, packet->stream->GetBuffer(), packet->stream->GetOffset());
	mSocket.Send(buffer, packet->header.size + PACKET_HEADER_SIZE);*/
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