#pragma once
#include "CommonLibrary.h"
#include "GameObject.h"

class Graphics;
class SpriteAnimation;

enum class ePlayerDirection
{
	Left,
	Right
};

enum class ePlayerState
{
	Idle,
	Move,
	Attack	
};

class Player : public GameObject
{
public:
	Player(int id, Position2D position, char dir, int hp);
	~Player();

	void MovePlayer(int dir);
	void Attack(int attackType);

	void OnFrameUpdate() override;
	void OnRender(Graphics& graphics) override;

private:
	void InitializeAnimation();
	void PlayAnimation();

	ePlayerDirection mCurrentDir;
	ePlayerState mCurrentState;
	std::unique_ptr<SpriteAnimation> mAnimation;

	int mHp;
	bool mIsMove;
	int mCurrentMoveDir;		//8πÊ«‚
	int mPrevMoveDir;
};

