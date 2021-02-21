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
	InitializeAnimation();
}

Player::~Player()
{

}

void Player::MovePlayer(int dir)
{
	switch (dir)
	{
	case dfPACKET_MOVE_DIR_LL:
		mPosition.x -= 3;
		break;
	case dfPACKET_MOVE_DIR_LU:
		mPosition.x -= 3;
		mPosition.y -= 2;
		break;
	case dfPACKET_MOVE_DIR_UU:
		mPosition.y -= 2;
		break;
	case dfPACKET_MOVE_DIR_RU:
		mPosition.x += 3;
		mPosition.y -= 2;
		break;
	case dfPACKET_MOVE_DIR_RR:
		mPosition.x += 3;
		break;
	case dfPACKET_MOVE_DIR_RD:
		mPosition.x += 3;
		mPosition.y += 2;
		break;
	case dfPACKET_MOVE_DIR_DD:
		mPosition.y += 2;
		break;
	case dfPACKET_MOVE_DIR_LD:
		mPosition.x -= 3;
		mPosition.y += 2;
		break;
	}
}

void Player::OnFrameUpdate()
{	
	mAnimation->Play(L"Move_R");	
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