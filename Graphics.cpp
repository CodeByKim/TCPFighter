#include "Graphics.h"
#include "Sprite.h"

Graphics::Graphics(ScreenMemoryBuffer& screenBuffer)
	: mScreenBuffer(screenBuffer)
{

}

Graphics::~Graphics()
{

}

void Graphics::Draw(Sprite* sprite, Position2D position)
{
	//-----------------------------------------------------------------
	// ��������Ʈ ����� ���� ������ ����.
	//-----------------------------------------------------------------
	BmpImageData bmp = sprite->GetBmpImageData();

	//-----------------------------------------------------------------
	// ��� ���� ����
	//-----------------------------------------------------------------
	int iDrawLen = 100;
	bmp.width = bmp.width * iDrawLen / 100;
	DWORD* memoryBuffer = (DWORD*)mScreenBuffer.memoryBuffer;
	DWORD* spriteBuffer = (DWORD*)bmp.image;

	//-----------------------------------------------------------------
	// ��� ���� ó��.
	//-----------------------------------------------------------------
	int drawX = position.x - sprite->GetPivot().x;
	int drawY = position.y - sprite->GetPivot().y;

	//-----------------------------------------------------------------
	// ��� �� ���� ��������Ʈ ��� ��ġ ���. (��� Ŭ����)
	//-----------------------------------------------------------------
	if (0 > drawY)
	{
		bmp.height = bmp.height - (-drawY);
		spriteBuffer = (DWORD*)(bmp.image + bmp.pitch * (-drawY));
		//-----------------------------------------------------------------
		// ������ ©���� ����̹Ƿ� ��������Ʈ ���� ��ġ�� �Ʒ��� �����ش�.
		//-----------------------------------------------------------------
		drawY = 0;
	}
	//-----------------------------------------------------------------
	// �ϴܿ� ������ ���. (�ϴ� Ŭ����)
	//-----------------------------------------------------------------
	if (mScreenBuffer.screenSize.height <= drawY + bmp.height)
	{
		bmp.height -= ((drawY + bmp.height) - mScreenBuffer.screenSize.height);
	}
	//-----------------------------------------------------------------
	// ���� ��� ��ġ ���. (���� Ŭ����)
	//-----------------------------------------------------------------
	if (0 > drawX)
	{
		bmp.width = bmp.width - (-drawX);
		spriteBuffer = spriteBuffer + (-drawX);
		//-----------------------------------------------------------------
		// ������ ���� �߸��Ƿ� ��� ���� ��ġ�� ���������� �δ�.
		//-----------------------------------------------------------------
		drawX = 0;
	}

	//-----------------------------------------------------------------
	// ������ ��� ��ġ ���. (���� Ŭ����)
	//-----------------------------------------------------------------
	if (mScreenBuffer.screenSize.width <= drawX + bmp.width)
	{
		bmp.width -= ((drawX + bmp.width) - mScreenBuffer.screenSize.width);
	}


	//-----------------------------------------------------------------
	// ���� �׸��� ���ٸ� �����Ѵ�.
	//-----------------------------------------------------------------
	if (bmp.width <= 0 || bmp.height <= 0)
		return;
	//-----------------------------------------------------------------
	// ȭ�鿡 ���� ��ġ�� �̵��Ѵ�.
	//-----------------------------------------------------------------
	memoryBuffer = (DWORD*)(((BYTE*)(memoryBuffer + drawX) + (drawY * mScreenBuffer.pitch)));
	BYTE* memoryBufferOrigin = (BYTE*)memoryBuffer;
	BYTE* spriteBufferOrigin = (BYTE*)spriteBuffer;
	//-----------------------------------------------------------------
	// ��ü ũ�⸦ ���鼭 ����� ó���� �Ѵ�.
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
		// �����ٷ� �̵�, ȭ��� ��������Ʈ ���..
		//-----------------------------------------------------------------
		memoryBufferOrigin = memoryBufferOrigin + screenPitch;
		spriteBufferOrigin = spriteBufferOrigin + spritePitch;
		memoryBuffer = (DWORD*)memoryBufferOrigin;
		spriteBuffer = (DWORD*)spriteBufferOrigin;
	}
}