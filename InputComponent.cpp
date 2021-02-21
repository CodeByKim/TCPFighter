#include "InputComponent.h"
#include "Game.h"
#include "Util.h"

void UpKeyCommand::Execute(TCPFighter& game)
{
	//game.MovePlayer(UP_KEY);
}

void DownKeyCommand::Execute(TCPFighter& game)
{
	//game.MovePlayer(DOWN_KEY);
}

void LeftKeyCommand::Execute(TCPFighter& game)
{
	//game.MovePlayer(LEFT_KEY);
}

void RightKeyCommand::Execute(TCPFighter& game)
{
	//game.MovePlayer(RIGHT_KEY);
}

void Attack1Command::Execute(TCPFighter& game)
{
	//game.MovePlayer(DOWN_KEY);
}

void Attack2Command::Execute(TCPFighter& game)
{
	//game.MovePlayer(LEFT_KEY);
}

void Attack3Command::Execute(TCPFighter& game)
{
	//game.MovePlayer(RIGHT_KEY);
}

InputComponent::InputComponent(Game& game)
	: BaseComponent(game)
{

}

bool left = false;
bool up = false;
bool right = false;
bool down = false;


void InputComponent::Update()
{	
	HandleMoveInput();
	HandleAttackInput();

	left = false;
	up = false;
	right = false;
	down = false;
}

eComponentType InputComponent::GetType()
{
	return eComponentType::Input;
}

void InputComponent::HandleMoveInput()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		
	{				
		left = true;
	}	

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{	
		up = true;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{		
		right = true;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{		
		down = true;
	}
	




	if (up && right)
	{
		Util::GetInstance().PrintLog(L"UR");
		return;
	}

	if (down && right)
	{
		Util::GetInstance().PrintLog(L"DR");
		return;
	}

	if (down && left)
	{
		Util::GetInstance().PrintLog(L"DL");
		return;
	}

	if (up && left)
	{
		Util::GetInstance().PrintLog(L"UL");
		return;
	}

	if (left)
	{
		Util::GetInstance().PrintLog(L"LL");
	}
	if (up)
	{
		Util::GetInstance().PrintLog(L"UU");
	}
	if (right)
	{
		Util::GetInstance().PrintLog(L"RR");
	}
	if (down)
	{
		Util::GetInstance().PrintLog(L"DD");
	}
	
}

void InputComponent::HandleAttackInput()
{
	if (GetAsyncKeyState('A') & 0x8000)
	{
		
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		
	}
}