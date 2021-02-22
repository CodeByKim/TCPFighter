#include "Socket.h"

Socket::Socket()
	: mSocket(INVALID_SOCKET)
	, mAddr {0, }	
{	
}

Socket::~Socket()
{

}

bool Socket::Create()
{
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mSocket == INVALID_SOCKET)
	{		
		MessageBox(NULL, L"socket()", L"Error", 0);
		return false;
	}

	SetNonblocking();
	return true;
}

bool Socket::Create(SOCKET sock, SOCKADDR_IN addr)
{
	mSocket = sock;
	mAddr = addr;

	SetNonblocking();
	return true;
}

bool Socket::Bind(std::string_view ip, unsigned short port)
{
	mAddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.data(), &mAddr.sin_addr.S_un.S_addr);
	mAddr.sin_port = htons(port);

	if (bind(mSocket, (SOCKADDR*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR)
	{		
		return false;
	}

	return true;
}

bool Socket::Listen()
{
	if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR)
	{		
		return false;
	}

	return true;
}

bool Socket::Connect(std::string_view ip, unsigned short port)
{
	mAddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.data(), &mAddr.sin_addr.S_un.S_addr);
	mAddr.sin_port = htons(SERVER_PORT);

	return connect(mSocket, (SOCKADDR*)&mAddr, sizeof(mAddr));
}

int Socket::Receive(char* buffer, int size)
{
	return recv(mSocket, buffer, size, 0);		
}

int Socket::Send(char* buffer, int size)
{	
	/*char buffer2[18];
	CopyMemory(buffer2 + 0, buffer + 0, 2);
	CopyMemory(buffer2 + 2, buffer + 2, 4);
	CopyMemory(buffer2 + 6, buffer + 6, 4);
	CopyMemory(buffer2 + 10, buffer + 10, 4);
	CopyMemory(buffer2 + 14, buffer + 14, 4);
	return send(mSocket, buffer2, 18, 0);*/

	return send(mSocket, buffer, size, 0);
}

void Socket::Close()
{
	closesocket(mSocket);
}

void Socket::SetNonblocking()
{
	u_long on = 1;
	ioctlsocket(mSocket, FIONBIO, &on);
}

SOCKET Socket::GetSocketHandle()
{
	return mSocket;
}