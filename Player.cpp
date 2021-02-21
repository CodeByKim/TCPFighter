#include "Player.h"
#include "Graphics.h"
#include "Util.h"
#include "SpriteAnimation.h"
#include "Resources.h"
#include "Graphics.h"

Player::Player(Position2D position, int id)
	: GameObject(position, id)
	, mAnimation(nullptr)
{	
	SpriteAnimation* animation = Resources::GetInstance().CreateSpriteAnimation();
	mAnimation.reset(animation);

	mAnimation->AddAnimation(L"Stand_L", 5);
	mAnimation->AddAnimation(L"Stand_R", 5);

	mAnimation->AddAnimation(L"Move_L", 4);
	mAnimation->AddAnimation(L"Move_R", 4);
	
	mAnimation->AddAnimation(L"Attack1_L", 3);
	mAnimation->AddAnimation(L"Attack1_R", 3);
	mAnimation->AddAnimation(L"Attack2_L", 4);
	mAnimation->AddAnimation(L"Attack2_R", 4);
	mAnimation->AddAnimation(L"Attack3_L", 4);
	mAnimation->AddAnimation(L"Attack3_R", 4);
}

Player::~Player()
{

}

void Player::OnFrameUpdate()
{	
	mAnimation->Play(L"Move_R");
	mPosition.x += 1;
}

void Player::OnRender(Graphics& graphics)
{
	graphics.Draw(mAnimation->GetCurrentSprite(), mPosition);
}