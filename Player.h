#pragma once
#include "CommonLibrary.h"
#include "GameObject.h"

class Graphics;
class Sprite;

class Player : public GameObject
{
public:
	Player(Position2D position, int id);
	~Player();

	void OnFrameUpdate() override;
	void OnRender(Graphics& graphics) override;

private:
	std::unique_ptr<Sprite> mPlayerSprite;
};

