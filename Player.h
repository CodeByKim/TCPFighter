#pragma once
#include "CommonLibrary.h"
#include "GameObject.h"

class Graphics;
class SpriteAnimation;
class TCPFighter;

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
	Player(int id, Position2D position, char dir, int hp, TCPFighter& game);
	~Player();

	void SetRemote();
	void MovePlayer(int dir);
	void Attack(int attackType);

	void RemoteMoveStart(char dir, int x, int y);
	void RemoteMoveStop(char dir, int x, int y);

	void OnFrameUpdate() override;
	void OnRender(Graphics& graphics) override;

private:
	void InitializeAnimation();
	void PlayAnimation();
	void MoveStart();
	void MoveStop();

	TCPFighter& mGame;
	ePlayerDirection mCurrentDir;
	ePlayerState mCurrentState;
	std::unique_ptr<SpriteAnimation> mAnimation;

	int mHp;
	bool mIsMove;
	bool mIsRemote;
	int mCurrentMoveDir;		//8πÊ«‚
	int mPrevMoveDir;
};

