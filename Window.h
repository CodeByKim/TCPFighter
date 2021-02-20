#pragma once
#include "CommonLibrary.h"

class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();
	
	void Run();

protected:
	virtual void FrameUpdate() = 0;

	HINSTANCE mhInstance;
	HWND mhWnd;

private:
	bool RegisterWindowClass();
	bool Create(int nCmdShow);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};