#pragma once
#include "CommonLibrary.h"
#include "Window.h"
#include "Connection.h"

class NetPacket;

class NetworkClient : public Window
{
public:
	NetworkClient(HINSTANCE hInstance, int nCmdShow);
	~NetworkClient();

protected:
	virtual void OnConnect() = 0;
	virtual void OnReceive(NetPacket* packet) = 0;
	virtual void OnDisconnect() = 0;

	bool Connect(std::string_view ip, unsigned short port);
	void SendPacket(std::shared_ptr<NetPacket> packet);
	void ProcessUserWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	void InitializeNetwork();

	Connection mConnection;
};