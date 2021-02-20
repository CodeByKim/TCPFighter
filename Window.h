#pragma once
#include "CommonLibrary.h"

class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();
	
	void Run();

private:
	bool RegisterWindowClass();
	bool Create(int nCmdShow);

	HINSTANCE mhInstance;
	HWND mhWnd;
};

