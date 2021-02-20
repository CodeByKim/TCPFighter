#pragma once
#include "CommonLibrary.h"

class Sprite
{
public:
	Sprite(BmpImageData data, DWORD colorKey = 0x00ffffff);
	~Sprite();

	Position2D& GetPivot();
	void SetPivot(Position2D pivot);
	void SetPivot(int x, int y);
	BmpImageData			GetBmpImageData();
	DWORD					GetColorKey();

private:
	BmpImageData mBmpImage;
	DWORD mColorKey;
	Position2D mPivot;	
};

