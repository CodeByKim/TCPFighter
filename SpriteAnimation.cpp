#include "SpriteAnimation.h"
#include "Resources.h"
#include "Sprite.h"

void SpriteAnimation::AddAnimation(std::wstring_view name, Position2D pivot, int delay)
{
	if (HasAnimation(name))
	{
		return;
	}

	SpriteAnimationInfo* info = new SpriteAnimationInfo;
	info->currentFrame = 0;
	info->delay = delay;

	auto spriteAnimationData = Resources::GetInstance().GetSpriteAnimationData(name);

	for (size_t i = 0; i < spriteAnimationData.size(); i++)
	{
		Sprite* sprite = Resources::GetInstance().CreateSprite(spriteAnimationData[i], pivot);				
		info->animation.push_back(sprite);		
	}

	mAnimations.insert(std::make_pair(name, info));
}

void SpriteAnimation::Play(std::wstring_view name)
{
    auto iter = mAnimations.find(name.data());
    SpriteAnimationInfo* anim = iter->second;

    //�켱.. Play�Լ��� �����Ӹ��� ����Ǵϱ� ����� �����Ű�����.. ������ �����ӽ�ŵ�̴�.
    if (mCurrentAnimation == nullptr)
    {
        mCurrentAnimation = anim;
        mCurrentAnimation->currentFrame = 0;
        mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    }

    if (mCurrentAnimation != anim)
    {
        mCurrentAnimation = anim;
        mCurrentAnimation->currentFrame = 0;
        mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    }

    if (mCurrentAnimation->delay <= frame)
    {
        int currentFrame = mCurrentAnimation->currentFrame;
        if (currentFrame >= mCurrentAnimation->animation.size())
        {
            ResetFrame();
        }
        else
        {
            NextFrame();

        }
        frame = 0;
    }

    frame += 1;
}

void SpriteAnimation::NextFrame()
{    
    mCurrentAnimation->currentSprite = mCurrentAnimation->animation[mCurrentAnimation->currentFrame];
    mCurrentAnimation->currentFrame += 1;
}

void SpriteAnimation::ResetFrame()
{
    mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    mCurrentAnimation->currentFrame = 0;
}

Sprite* SpriteAnimation::GetCurrentSprite()
{
    if (mCurrentAnimation == nullptr)
        return nullptr;

    return mCurrentAnimation->currentSprite;
}

bool SpriteAnimation::HasAnimation(std::wstring_view name)
{
	auto iter = mAnimations.find(name.data());
	if (iter != mAnimations.end())
	{
		return true;
	}

	return false;
}