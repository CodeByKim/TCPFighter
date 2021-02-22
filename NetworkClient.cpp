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

void NetworkClient::ProcessUserWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case UM_SOCKET:
        {
            switch (WSAGETSELECTEVENT(lParam))
            {
            case FD_CONNECT:
                break;
            case FD_READ:
                break;
            case FD_WRITE:
                break;
            case FD_CLOSE:
                break;
            }            
        }
        break;
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