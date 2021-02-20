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

private:
	bool RegisterWindowClass();
	bool Create(int nCmdShow);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HINSTANCE mhInstance;
	HWND mhWnd;
};