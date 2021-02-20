#pragma once

#include "CommonLibrary.h"

struct ScreenSize
{
	int width;
	int height;
};

struct ScreenMemoryBuffer
{
	ScreenSize screenSize;
	BYTE* memoryBuffer;
	int bufferSize;
	int pitch;
	int colorBit;	
};

