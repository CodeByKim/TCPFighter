#pragma once
#include "CommonLibrary.h"
#include "ScreenMemoryBuffer.h"

class Sprite;

class Graphics
{
public:
	Graphics(HWND hWnd, ScreenSize screenSize);
	~Graphics();

	void Draw(Sprite* sprite, Position2D position);
	void Render();

private:	
	void CreateDibBuffer(int width, int height, int colorBit);
	void ReleaseDibBuffer();

	BITMAPINFO mDibInfo;
	ScreenMemoryBuffer mScreenBuffer;
	HWND mhWnd;
	HDC mDC;
};

