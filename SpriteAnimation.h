#pragma once
#include "CommonLibrary.h"

class Sprite;

struct SpriteAnimationInfo
{
	int delay;	
	std::vector<Sprite*> animation;
	Sprite* currentSprite;
};

class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

	void AddAnimation(std::wstring_view name, Position2D pivot, int delay);
	void Play(std::wstring_view name);
	Sprite* GetCurrentSprite();

private:
	bool HasAnimation(std::wstring_view name);
	void NextFrame();

	std::unordered_map<std::wstring, SpriteAnimationInfo*> mAnimations;
	SpriteAnimationInfo* mCurrentAnimation;
	int mCurrentFrame;
	int mCurrentAnimationIndex;
};

