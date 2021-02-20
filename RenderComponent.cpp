#include "RenderComponent.h"
#include "Util.h"
#include "GameObject.h"

RenderComponent::RenderComponent(HWND hWnd)
	: mhWnd(hWnd)
	, mGraphics(mScreenBuffer)
{
	ZeroMemory(&mDibInfo, sizeof(BITMAPINFO));
	CreateDibBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	mDC = GetDC(mhWnd);
}

RenderComponent::~RenderComponent()
{
	ReleaseDibBuffer();
}

void RenderComponent::DrawSprite(Sprite* sprite, Position2D pos)
{
	mGraphics.Draw(sprite, pos);
}

void RenderComponent::Update(std::vector<std::unique_ptr<GameObject>>& objects)
{
	Util::GetInstance().PrintLog(L"Update RenderComponent...");

	if (mScreenBuffer.memoryBuffer == nullptr)
		return;

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->OnRender(mGraphics);
	}

	SetDIBitsToDevice(mDC, 0, 0, mScreenBuffer.screenSize.width, mScreenBuffer.screenSize.height,
		0, 0, 0, mScreenBuffer.screenSize.height,
		mScreenBuffer.memoryBuffer, &mDibInfo,
		DIB_RGB_COLORS);
}

eComponentType RenderComponent::GetType()
{
	return eComponentType::Render;
}

void RenderComponent::CreateDibBuffer(int width, int height, int colorBit)
{
	mScreenBuffer.screenSize.width = width;
	mScreenBuffer.screenSize.height = height;

	mScreenBuffer.colorBit = colorBit;
	mScreenBuffer.pitch = ((width * (colorBit / 8)) + 3) & ~3;
	mScreenBuffer.bufferSize = mScreenBuffer.pitch * height;

	//------------------------------------------------------------------
	// DibInfo 헤더 생성
	// DIB 출력시 뒤집어서 출력하기 위해 높이값을 - 로 입력하고 있다.
	//------------------------------------------------------------------
	mDibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mDibInfo.bmiHeader.biWidth = width;
	mDibInfo.bmiHeader.biHeight = -height;
	mDibInfo.bmiHeader.biPlanes = 1;
	mDibInfo.bmiHeader.biBitCount = colorBit;
	mDibInfo.bmiHeader.biCompression = 0;
	mDibInfo.bmiHeader.biSizeImage = mScreenBuffer.bufferSize;
	mDibInfo.bmiHeader.biXPelsPerMeter = 0;
	mDibInfo.bmiHeader.biYPelsPerMeter = 0;
	mDibInfo.bmiHeader.biClrUsed = 0;
	mDibInfo.bmiHeader.biClrImportant = 0;

	//------------------------------------------------------------------
	// 버퍼 생성
	//------------------------------------------------------------------
	mScreenBuffer.memoryBuffer = new BYTE[mScreenBuffer.bufferSize];
	memset(mScreenBuffer.memoryBuffer, 0xff, mScreenBuffer.bufferSize);
}

void RenderComponent::ReleaseDibBuffer()
{
	memset(&mDibInfo, 0x00, sizeof(BITMAPINFO));

	if (mScreenBuffer.memoryBuffer != nullptr)
		delete[] mScreenBuffer.memoryBuffer;

	mScreenBuffer.memoryBuffer = nullptr;
	ReleaseDC(mhWnd, mDC);
}