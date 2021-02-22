#pragma once
#include "CommonLibrary.h"

class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();
	
	void Run();
	void SetScreenSize(int screenWidth, int screenHeight);	

protected:
	virtual void FrameUpdate() = 0;
	virtual void ProcessUserWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

	HINSTANCE mhInstance;
	HWND mhWnd;
	ScreenSize mScreenSize;

private:
	bool RegisterWindowClass();
	bool Create(int nCmdShow);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};