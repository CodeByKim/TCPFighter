#include "Player.h"
#include "Graphics.h"
#include "Util.h"
#include "Sprite.h"
#include "Resources.h"
#include "Graphics.h"

Player::Player(Position2D position, int id)
	: GameObject(position, id)
{
	Sprite* sprite = Resources::GetInstance().CreateSprite(L"Stand", position.x, position.y);
	mPlayerSprite.reset(sprite);
}

Player::~Player()
{

}

void Player::OnFrameUpdate()
{
	mPosition.x += 1;
}

void Player::OnRender(Graphics& graphics)
{
	graphics.Draw(mPlayerSprite.get(), mPosition);
}