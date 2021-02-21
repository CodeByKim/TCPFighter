#include "Player.h"
#include "Graphics.h"
#include "Util.h"
#include "SpriteAnimation.h"
#include "Resources.h"
#include "Graphics.h"

Player::Player(Position2D position, int id)
	: GameObject(position, id)
	, mAnimation(nullptr)
	, mCurrentDir(ePlayerDirection::Right)
	, mCurrentState(ePlayerState::Idle)
{	
	InitializeAnimation();
}

Player::~Player()
{

}

void Player::MovePlayer(int dir)
{
	Position2D offset[8] = {
		{-3, 0},
		{-3, -2},
		{0, -2},
		{3, -2},
		{3, 0},
		{3, 2},
		{0, 2},
		{-3, 2}
	};

	mPosition.x += offset[dir].x;
	mPosition.y += offset[dir].y;

	switch (mCurrentDir)
	{
	case ePlayerDirection::Left:
		if (offset[dir].x > 0)
		{			
			mCurrentDir = ePlayerDirection::Right;						
		}		
		break;
	case ePlayerDirection::Right:
		if (offset[dir].x < 0)
		{			
			mCurrentDir = ePlayerDirection::Left;			
		}		
		break;
	}	

	mCurrentState = ePlayerState::Move;	
}

void Player::Attack(int attackType)
{
	mCurrentState = ePlayerState::Attack;
}

void Player::OnFrameUpdate()
{	
	if (mCurrentState == ePlayerState::Idle)
	{
		if (mCurrentDir == ePlayerDirection::Left)
		{
			mAnimation->Play(L"Stand_L");
		}
		else
		{
			mAnimation->Play(L"Stand_R");
		}
	}
	else if(mCurrentState == ePlayerState::Move)
	{
		if (mCurrentDir == ePlayerDirection::Left)
		{
			mAnimation->Play(L"Move_L");
		}
		else
		{
			mAnimation->Play(L"Move_R");
		}
	}
	else if (mCurrentState == ePlayerState::Attack)
	{
		mAnimation->Play(L"Attack3_R");
	}

	mCurrentState = ePlayerState::Idle;
}

void Player::OnRender(Graphics& graphics)
{
	graphics.Draw(mAnimation->GetCurrentSprite(), mPosition);
}

void Player::InitializeAnimation()
{
	Position2D pivot = { 71, 90 };
	SpriteAnimation* animation = Resources::GetInstance().CreateSpriteAnimation();
	mAnimation.reset(animation);

	mAnimation->AddAnimation(L"Stand_L", pivot, 5);
	mAnimation->AddAnimation(L"Stand_R", pivot, 5);

	mAnimation->AddAnimation(L"Move_L", pivot, 4);
	mAnimation->AddAnimation(L"Move_R", pivot, 4);

	mAnimation->AddAnimation(L"Attack1_L", pivot, 3);
	mAnimation->AddAnimation(L"Attack1_R", pivot, 3);
	mAnimation->AddAnimation(L"Attack2_L", pivot, 4);
	mAnimation->AddAnimation(L"Attack2_R", pivot, 4);
	mAnimation->AddAnimation(L"Attack3_L", pivot, 4);
	mAnimation->AddAnimation(L"Attack3_R", pivot, 4);
}