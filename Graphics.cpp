#include "Graphics.h"
#include "Sprite.h"

Graphics::Graphics(HWND hWnd, ScreenSize screenSize)
	: mhWnd(hWnd)
{
	mDC = GetDC(mhWnd);
	ZeroMemory(&mDibInfo, sizeof(BITMAPINFO));
	CreateDibBuffer(screenSize.width, screenSize.height, COLOR_BIT);
}

Graphics::~Graphics()
{
	ReleaseDibBuffer();
}

void Graphics::Draw(Sprite* sprite, Position2D position)
{
	//-----------------------------------------------------------------
	// 스프라이트 출력을 위해 사이즈 저장.
	//-----------------------------------------------------------------
	BmpImageData bmp = sprite->GetBmpImageData();

	//-----------------------------------------------------------------
	// 출력 길이 설정
	//-----------------------------------------------------------------
	int iDrawLen = 100;
	bmp.width = bmp.width * iDrawLen / 100;
	DWORD* memoryBuffer = (DWORD*)mScreenBuffer.memoryBuffer;
	DWORD* spriteBuffer = (DWORD*)bmp.image;

	//-----------------------------------------------------------------
	// 출력 중점 처리.
	//-----------------------------------------------------------------
	int drawX = position.x - sprite->GetPivot().x;
	int drawY = position.y - sprite->GetPivot().y;

	//-----------------------------------------------------------------
	// 상단 에 대한 스프라이트 출력 위치 계산. (상단 클리핑)
	//-----------------------------------------------------------------
	if (0 > drawY)
	{
		bmp.height = bmp.height - (-drawY);
		spriteBuffer = (DWORD*)(bmp.image + bmp.pitch * (-drawY));
		//-----------------------------------------------------------------
		// 윗쪽이 짤리는 경우이므로 스프라이트 시작 위치를 아래로 내려준다.
		//-----------------------------------------------------------------
		drawY = 0;
	}
	//-----------------------------------------------------------------
	// 하단에 사이즈 계산. (하단 클리핑)
	//-----------------------------------------------------------------
	if (mScreenBuffer.screenSize.height <= drawY + bmp.height)
	{
		bmp.height -= ((drawY + bmp.height) - mScreenBuffer.screenSize.height);
	}
	//-----------------------------------------------------------------
	// 왼쪽 출력 위치 계산. (좌측 클리핑)
	//-----------------------------------------------------------------
	if (0 > drawX)
	{
		bmp.width = bmp.width - (-drawX);
		spriteBuffer = spriteBuffer + (-drawX);
		//-----------------------------------------------------------------
		// 왼쪽이 조금 잘리므로 출력 시작 위치를 오른쪽으로 민다.
		//-----------------------------------------------------------------
		drawX = 0;
	}

	//-----------------------------------------------------------------
	// 오른쪽 출력 위치 계산. (우측 클리핑)
	//-----------------------------------------------------------------
	if (mScreenBuffer.screenSize.width <= drawX + bmp.width)
	{
		bmp.width -= ((drawX + bmp.width) - mScreenBuffer.screenSize.width);
	}


	//-----------------------------------------------------------------
	// 찍을 그림이 없다면 종료한다.
	//-----------------------------------------------------------------
	if (bmp.width <= 0 || bmp.height <= 0)
		return;
	//-----------------------------------------------------------------
	// 화면에 찍을 위치로 이동한다.
	//-----------------------------------------------------------------
	memoryBuffer = (DWORD*)(((BYTE*)(memoryBuffer + drawX) + (drawY * mScreenBuffer.pitch)));
	BYTE* memoryBufferOrigin = (BYTE*)memoryBuffer;
	BYTE* spriteBufferOrigin = (BYTE*)spriteBuffer;
	//-----------------------------------------------------------------
	// 전체 크기를 돌면서 투명색 처리를 한다.
	//-----------------------------------------------------------------

	int height = bmp.height;
	int width = bmp.width;
	DWORD colorKey = sprite->GetColorKey();
	int screenPitch = mScreenBuffer.pitch;
	int spritePitch = bmp.pitch;
	for (int iCountY = 0; height > iCountY; iCountY++)
	{
		for (int iCountX = 0; width > iCountX; iCountX++)
		{
			if (colorKey != (*spriteBuffer & 0x00ffffff))
			{
				*memoryBuffer = *spriteBuffer;
			}

			memoryBuffer++;
			spriteBuffer++;
		}

		//-----------------------------------------------------------------
		// 다음줄로 이동, 화면과 스프라이트 모두..
		//-----------------------------------------------------------------
		memoryBufferOrigin = memoryBufferOrigin + screenPitch;
		spriteBufferOrigin = spriteBufferOrigin + spritePitch;
		memoryBuffer = (DWORD*)memoryBufferOrigin;
		spriteBuffer = (DWORD*)spriteBufferOrigin;
	}
}

void Graphics::Render()
{
	SetDIBitsToDevice(mDC, 0, 0, mScreenBuffer.screenSize.width, mScreenBuffer.screenSize.height,
		0, 0, 0, mScreenBuffer.screenSize.height,
		mScreenBuffer.memoryBuffer, &mDibInfo,
		DIB_RGB_COLORS);
}

void Graphics::CreateDibBuffer(int width, int height, int colorBit)
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

void Graphics::ReleaseDibBuffer()
{
	memset(&mDibInfo, 0x00, sizeof(BITMAPINFO));

	if (mScreenBuffer.memoryBuffer != nullptr)
		delete[] mScreenBuffer.memoryBuffer;

	mScreenBuffer.memoryBuffer = nullptr;
	ReleaseDC(mhWnd, mDC);
}