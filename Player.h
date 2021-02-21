#pragma once
#include "CommonLibrary.h"
#include "GameObject.h"

class Graphics;
class SpriteAnimation;

class Player : public GameObject
{
public:
	Player(Position2D position, int id);
	~Player();

	void MovePlayer(int dir);
	void OnFrameUpdate() override;
	void OnRender(Graphics& graphics) override;

private:
	void InitializeAnimation();

	std::unique_ptr<SpriteAnimation> mAnimation;
};

