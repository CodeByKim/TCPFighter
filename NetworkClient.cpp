#include "NetworkClient.h"
#include "Window.h"
#include "Util.h"

NetworkClient::NetworkClient(HINSTANCE hInstance, int nCmdShow)
	: Window(hInstance, nCmdShow)
{
	InitializeNetwork();
}

NetworkClient::~NetworkClient()
{
	WSACleanup();
}

bool NetworkClient::Connect(std::string_view ip, unsigned short port)
{
    return mConnection.Connect(ip, port);
}

void NetworkClient::SendPacket(std::shared_ptr<NetPacket> packet)
{
    mConnection.SendPacket(packet);
}

void NetworkClient::ProcessUserWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == UM_SOCKET)
    {
        switch (WSAGETSELECTEVENT(lParam))
        {
        case FD_CONNECT:
        {
            OnConnect();
        }
        break;

        case FD_READ:
        {
            int recvSize = mConnection.Receive();
            if (recvSize > 0)
            {
                std::queue<std::shared_ptr<NetPacket>> packetQueue;
                mConnection.GetPacket(&packetQueue);

                while (!packetQueue.empty())
                {
                    auto packet = packetQueue.front();
                    packetQueue.pop();

                    OnReceive(packet.get());
                }
            }
            else
            {
                OnDisconnect();
            }
        }
        break;

        case FD_WRITE:
            break;

        case FD_CLOSE:
            OnDisconnect();
            break;
        }
    }    
}

void NetworkClient::InitializeNetwork()
{
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
    {        
        Util::GetInstance().ShowMessageBox(L"Error : WSAStartup()");
        return;
    }

    mConnection.Initialize();

    if (WSAAsyncSelect(mConnection.GetSocketHandle(),
        mhWnd, UM_SOCKET, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
    {
        Util::GetInstance().ShowMessageBox(L"Error : WSAAsyncSelect()");        
        return;
    }
}

void NetworkClient::CloseNetwork()
{
    mConnection.Release();
}