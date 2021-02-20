#include "Sprite.h"

Sprite::Sprite(BmpImageData data, DWORD colorKey)
    : mBmpImage(data), mColorKey(colorKey)
{
    mPivot = { 0, 0 };
}

Sprite::~Sprite()
{
    if (!mBmpImage.image)
        delete mBmpImage.image;
}

Position2D& Sprite::GetPivot()
{
    return mPivot;
}

void Sprite::SetPivot(Position2D pivot)
{
    mPivot = pivot;
}

void Sprite::SetPivot(int x, int y)
{
    mPivot.x = x;
    mPivot.y = y;
}