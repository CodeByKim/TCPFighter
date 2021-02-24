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
		//sendQueue�� �����͸� ���־��ٰ�?
		//�ٷ� ��Ŀ��Ʈ
		mSocket.Close();
	}
	
	//sendQueue�� ���̷ε� ����
	if (!mSendBuffer.Enqueue(packet->stream->GetBuffer(), packet->header.size))
	{
		//sendQueue�� �����͸� ���־��ٰ�?
		//�ϴ� ��� ������ �������߰ڳ�
		
		mSendBuffer.MoveFront(PACKET_HEADER_SIZE);
		mSocket.Close();
	}

	//sendQueue�� �ִ� ��� ������ �����ؾ� ��
	while (true)
	{
		//����ִٸ� ���� �� �����Ŵϱ� Ż��
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
					//������ ���� �۽�ť ������ ������... ���߿� �����ؾ���
					//�ϴ��� ������.. �� ������ ������.
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
			//�����ΰǵ�...
		}
	}

	//���� �� �۵��ߴ� �ڵ�
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