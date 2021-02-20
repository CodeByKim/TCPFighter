#pragma once

#include "CommonLibrary.h"

struct ScreenMemoryBuffer
{
	ScreenSize screenSize;
	BYTE* memoryBuffer;
	int bufferSize;
	int pitch;
	int colorBit;	
};

