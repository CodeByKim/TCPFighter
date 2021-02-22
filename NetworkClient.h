#pragma once
#include "CommonLibrary.h"
#include "Window.h"
#include "Connection.h"

class Packet;

class NetworkClient : public Window
{
public:
	NetworkClient(HINSTANCE hInstance, int nCmdShow);
	~NetworkClient();

protected:
	virtual void OnConnect() = 0;
	virtual void OnReceive(Packet* packet) = 0;
	virtual void OnDisconnect() = 0;

	void ProcessUserWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	void InitializeNetwork();

	Connection mConnection;
};

