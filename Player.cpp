#include "Player.h"
#include "Graphics.h"
#include "Util.h"
#include "SpriteAnimation.h"
#include "Resources.h"
#include "Graphics.h"
#include "NetPacket.h"
#include "TCPFighter.h"

Player::Player(int id, Position2D position, char dir, int hp, TCPFighter& game)
	: GameObject(position, id)
	, mAnimation(nullptr)
	, mCurrentDir(dir == dfPACKET_MOVE_DIR_LL ? ePlayerDirection::Left : ePlayerDirection::Right)
	, mCurrentState(ePlayerState::Idle)
	, mHp(hp)
	, mIsMove(false)
	, mCurrentMoveDir(dir)
	, mPrevMoveDir(dir)
	, mGame(game)
	, mIsRemote(false)
	, mIsAttack(false)
{	
	InitializeAnimation();
}

Player::~Player()
{

}

void Player::SetRemote()
{
	mIsRemote = true;
}

void Player::MovePlayer(int dir)
{	
	if (mCurrentState == ePlayerState::Attack)
	{
		return;
	}

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

	mIsMove = true;
	
	mPrevMoveDir = mCurrentMoveDir;
	mCurrentMoveDir = dir;
}

void Player::Hit(char damage)
{
	Util::GetInstance().PrintLog(L"Hit...");
	mHp = damage;

	if (mHp <= 0)
	{
		Util::GetInstance().PrintLog(L"Im Die...");
	}
}

int attack;		//이게 뭐지.......
void Player::Attack(int attackType)
{	
	attack = attackType;

	mIsAttack = true;
}

void Player::RemoteMoveStart(char dir, int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
	MovePlayer(dir);

	mCurrentState = ePlayerState::Move;
}

void Player::RemoteAttack1(char dir, int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;

	if (dir == dfPACKET_MOVE_DIR_LL)
	{
		mCurrentDir = ePlayerDirection::Left;
	}
	else if (dir == dfPACKET_MOVE_DIR_RR)
	{
		mCurrentDir = ePlayerDirection::Right;
	}	
	
	Attack(dfPACKET_CS_ATTACK1);
	mCurrentState = ePlayerState::Attack;
}

void Player::RemoteAttack2(char dir, int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;

	if (dir == dfPACKET_MOVE_DIR_LL)
	{
		mCurrentDir = ePlayerDirection::Left;
	}
	else if (dir == dfPACKET_MOVE_DIR_RR)
	{
		mCurrentDir = ePlayerDirection::Right;
	}

	Attack(dfPACKET_CS_ATTACK2);
	mCurrentState = ePlayerState::Attack;
}

void Player::RemoteAttack3(char dir, int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;

	if (dir == dfPACKET_MOVE_DIR_LL)
	{
		mCurrentDir = ePlayerDirection::Left;
	}
	else if (dir == dfPACKET_MOVE_DIR_RR)
	{
		mCurrentDir = ePlayerDirection::Right;
	}

	Attack(dfPACKET_CS_ATTACK3);
	mCurrentState = ePlayerState::Attack;
}

void Player::RemoteMoveStop(char dir, int x, int y)
{
	mIsMove = false;

	mPosition.x = x;
	mPosition.y = y;

	mCurrentState = ePlayerState::Idle;
}

void Player::OnFrameUpdate()
{		
	switch(mCurrentState)
	{
		case ePlayerState::Idle:
		{
			if (mIsMove)
			{		
				if (!mIsRemote)
				{
					MoveStart();
				}				
			}

			if (mIsAttack)
			{				
				if (!mIsRemote)
					AttackStart(attack);
			}
		}
		break;

		case ePlayerState::Move:
		{
			//이동 방향이 바뀜
			if (mPrevMoveDir != mCurrentMoveDir)
			{			
				if (!mIsRemote)
				{
					MoveStop();
					MoveStart();
				}				
			}

			if (!mIsMove)
			{				
				if (!mIsRemote)
				{
					MoveStop();
				}				
			}		

			if (mIsRemote)
			{
				Util::GetInstance().PrintLog(L"Remote Move");
				MovePlayer(mCurrentMoveDir);
			}
		}
		break;

		case ePlayerState::Attack:
		{

		}
		break;
	}

	PlayAnimation();

	if (!mIsRemote)
	{
		mIsMove = false;
	}	
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

void Player::PlayAnimation()
{
	if (mCurrentDir == ePlayerDirection::Left)
	{
		switch (mCurrentState)
		{
		case ePlayerState::Idle:
			mAnimation->Play(L"Stand_L");
			break;
		case ePlayerState::Move:
			mAnimation->Play(L"Move_L");
			break;
		case ePlayerState::Attack:
			if (attack == dfPACKET_CS_ATTACK1)
				mAnimation->Play(L"Attack1_L");
			else if (attack == dfPACKET_CS_ATTACK2)
				mAnimation->Play(L"Attack2_L");
			else
				mAnimation->Play(L"Attack3_L");

			mAnimation->mEndEventCallback = [this]() {
				mCurrentState = ePlayerState::Idle;
				mIsAttack = false;
			};
			break;
		}
	}
	else
	{
		switch (mCurrentState)
		{
		case ePlayerState::Idle:
			mAnimation->Play(L"Stand_R");
			break;
		case ePlayerState::Move:
			mAnimation->Play(L"Move_R");
			break;
		case ePlayerState::Attack:
			if (attack == dfPACKET_CS_ATTACK1)
				mAnimation->Play(L"Attack1_R");
			else if (attack == dfPACKET_CS_ATTACK2)
				mAnimation->Play(L"Attack2_R");
			else
				mAnimation->Play(L"Attack3_R");

			mAnimation->mEndEventCallback = [this]() {
				mCurrentState = ePlayerState::Idle;
				mIsAttack = false;
			};
			break;
		}
	}
}

void Player::MoveStart()
{	
	char direction = mCurrentMoveDir;
	short x = mPosition.x;
	short y = mPosition.y;

	std::shared_ptr<NetPacket> packet = std::make_shared<NetPacket>();
	*packet << direction << x << y;
	packet->SetHeader(dfPACKET_CS_MOVE_START);
	mGame.SendPacket(packet);

	mCurrentState = ePlayerState::Move;
}

void Player::MoveStop()
{	
	char direction = mCurrentMoveDir;
	short x = mPosition.x;
	short y = mPosition.y;

	std::shared_ptr<NetPacket> packet = std::make_shared<NetPacket>();
	*packet << direction << x << y;
	packet->SetHeader(dfPACKET_CS_MOVE_STOP);	
	mGame.SendPacket(packet);

	mCurrentState = ePlayerState::Idle;
}

void Player::AttackStart(int attackType)
{	
	char direction = mCurrentMoveDir;
	short x = mPosition.x;
	short y = mPosition.y;

	std::shared_ptr<NetPacket> packet = std::make_shared<NetPacket>();
	*packet << direction << x << y;
	packet->SetHeader(attackType);
	mGame.SendPacket(packet);

	mCurrentState = ePlayerState::Attack;
}