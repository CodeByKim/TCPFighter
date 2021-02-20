#pragma once
#include "CommonLibrary.h"
#include "ScreenMemoryBuffer.h"

class Sprite;

class Graphics
{
public:
	Graphics(ScreenMemoryBuffer& screenBuffer);
	~Graphics();

	void Draw(Sprite* sprite, Position2D position);

private:
	ScreenMemoryBuffer& mScreenBuffer;
};

