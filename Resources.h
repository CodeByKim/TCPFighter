#pragma once
#include "CommonLibrary.h"

class Sprite;
class SpriteAnimation;

class Resources
{
public:
	void LoadSprite(std::wstring_view path, Position2D pivot);
	void LoadSpriteAnimation(std::wstring_view path, Position2D pivot);

	Sprite* CreateSprite(BmpImageData spriteData);
	Sprite* CreateSprite(std::wstring_view name);
	SpriteAnimation* CreateSpriteAnimation();

	std::vector<BmpImageData>& GetSpriteAnimationData(std::wstring_view name);

	static Resources& GetInstance();

private:
	bool LoadBmpImage(BmpImageData* bmpImage, const wchar_t* fileName);

	std::unordered_map<std::wstring, std::vector<BmpImageData>*> mSpriteAnimations;
	std::unordered_map<std::wstring, BmpImageData> mSprites;
};