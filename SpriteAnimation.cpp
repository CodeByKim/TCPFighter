#include "SpriteAnimation.h"
#include "Resources.h"
#include "Sprite.h"

SpriteAnimation::SpriteAnimation()
    : mCurrentFrame(0)
    , mCurrentAnimationIndex(0)
{

}

SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::AddAnimation(std::wstring_view name, Position2D pivot, int delay)
{
	if (HasAnimation(name))
	{
		return;
	}

	SpriteAnimationInfo* info = new SpriteAnimationInfo;	
    mCurrentAnimationIndex = 0;
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

    //우선.. Play함수는 프레임마다 실행되니까 상관은 없을거같은데.. 문제는 프레임스킵이다.
    if (mCurrentAnimation == nullptr)
    {
        mCurrentAnimation = anim;        
        mCurrentAnimationIndex = 0;
        mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    }

    if (mCurrentAnimation != anim)
    {
        mCurrentAnimation = anim;        
        mCurrentAnimationIndex = 0;
        mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    }

    if (mCurrentAnimation->delay <= mCurrentFrame)
    {        
        if (mCurrentAnimationIndex >= mCurrentAnimation->animation.size())
        {
            mCurrentAnimationIndex = 0;
            //여기서 Attack 애니메이션이라면 Idle로 되돌아가야 함
            if (mEndEventCallback != nullptr)
            {
                mEndEventCallback();
                return;
            }
        }

        NextFrame();
        mCurrentFrame = 0;
    }
    else
    {
        mCurrentFrame += 1;
    }
}

void SpriteAnimation::NextFrame()
{
    mCurrentAnimation->currentSprite = mCurrentAnimation->animation[mCurrentAnimationIndex];
    mCurrentAnimationIndex += 1;
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