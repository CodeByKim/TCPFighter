#include "Resources.h"
#include "Sprite.h"
#include "SpriteAnimation.h"

Resources& Resources::GetInstance()
{
	static Resources instance;
	return instance;
}

void Resources::LoadSprite(std::wstring_view path)
{
	auto spriteIter = mSpriteAnimations.find(path.data());
	if (spriteIter != mSpriteAnimations.end())
	{
		return;
	}

	std::filesystem::path basePath(L"./SpriteData");
	std::filesystem::path filePath(std::wstring(path.data()).append(L".bmp"));

	BmpImageData data;	
	LoadBmpImage(&data, (basePath / filePath).c_str());
	mSprites.insert(std::make_pair(path, data));
}

void Resources::LoadSpriteAnimation(std::wstring_view path)
{
	auto spriteIter = mSpriteAnimations.find(path.data());
	if (spriteIter != mSpriteAnimations.end())
	{
		return;
	}

	std::vector<BmpImageData>* sprites = new std::vector<BmpImageData>();
	std::filesystem::path basePath(L"./SpriteData");
	std::filesystem::directory_iterator iter(basePath / path);

	while (iter != std::filesystem::end(iter))
	{
		BmpImageData data;
		const wchar_t* spritePath = iter->path().c_str();

		if (LoadBmpImage(&data, spritePath))
		{
			sprites->push_back(data);
			++iter;
		}
	}

	mSpriteAnimations.insert(std::make_pair(path, sprites));
}

Sprite* Resources::CreateSprite(std::wstring_view name, Position2D pivot)
{	
	Sprite* sprite = new Sprite(mSprites[name.data()]);
	sprite->SetPivot(pivot);

	return sprite;
}

Sprite* Resources::CreateSprite(BmpImageData spriteData, Position2D pivot)
{
	Sprite* sprite = new Sprite(spriteData);
	sprite->SetPivot(pivot);

	return sprite;
}

SpriteAnimation* Resources::CreateSpriteAnimation()
{
	return new SpriteAnimation();
}

std::vector<BmpImageData>& Resources::GetSpriteAnimationData(std::wstring_view name)
{
	return *mSpriteAnimations[name.data()];
}

bool Resources::LoadBmpImage(BmpImageData* bmpImage, const wchar_t* fileName)
{
	HANDLE hFile;
	DWORD dwRead;
	BITMAPFILEHEADER stFileHeader;
	BITMAPINFOHEADER stInfoHeader;

	if (bmpImage == nullptr)
	{
		return false;
	}

	//파일 오픈
	hFile = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	ReadFile(hFile, &stFileHeader, sizeof(BITMAPFILEHEADER), &dwRead, NULL);

	if (0x4d42 == stFileHeader.bfType)
	{
		//-----------------------------------------------------------------
		// 인포헤더를 읽어서 저장 & 32비트 확인.
		//-----------------------------------------------------------------
		ReadFile(hFile, &stInfoHeader, sizeof(BITMAPINFOHEADER), &dwRead, NULL);
		if (32 == stInfoHeader.biBitCount)
		{
			int pitch = (stInfoHeader.biWidth * 4) + 3 & ~3;
			int width = stInfoHeader.biWidth;
			int height = stInfoHeader.biHeight;

			bmpImage->pitch = pitch;
			bmpImage->width = width;
			bmpImage->height = height;

			//-----------------------------------------------------------------
			// 이미지에 대한 전체 크기를 구하고, 메모리 할당.
			//-----------------------------------------------------------------
			int imageSize = pitch * height;
			bmpImage->image = new BYTE[imageSize];

			//-----------------------------------------------------------------
			// 이미지 부분은 스프라이트 버퍼로 읽어온다.
			// DIB 는 뒤집어져 있으므로 이를 다시 뒤집자.
			// 임시 버퍼에 읽은 뒤에 뒤집으면서 복사한다.
			//-----------------------------------------------------------------
			BYTE* bypTempBuffer = new BYTE[imageSize];
			BYTE* bypSpriteTemp = bmpImage->image;
			BYTE* bypTurnTemp;
			ReadFile(hFile, bypTempBuffer, imageSize, &dwRead, NULL);

			//-----------------------------------------------------------------
			// 한줄한줄 뒤집자.
			//-----------------------------------------------------------------
			bypTurnTemp = bypTempBuffer + pitch * (stInfoHeader.biHeight - 1);
			for (int iCount = 0; iCount < stInfoHeader.biHeight; iCount++)
			{
				memcpy(bypSpriteTemp, bypTurnTemp, pitch);
				bypSpriteTemp += pitch;
				bypTurnTemp -= pitch;
			}

			delete[] bypTempBuffer;
			CloseHandle(hFile);
			return true;
		}
	}

	CloseHandle(hFile);
	return false;
}