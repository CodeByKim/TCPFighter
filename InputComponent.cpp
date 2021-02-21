#include "InputComponent.h"
#include "Game.h"
#include "Util.h"

#pragma region Commands...
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
#pragma endregion

void InputComponent::Update()
{	
	HandleMoveInput();
	HandleAttackInput();
}

eComponentType InputComponent::GetType()
{
	return eComponentType::Input;
}

void InputComponent::HandleMoveInput()
{
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) 
		&& (GetAsyncKeyState(VK_UP) & 0x8000))
	{
		Util::GetInstance().PrintLog(L"UL");
		return;
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)
		&& (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		Util::GetInstance().PrintLog(L"DL");
		return;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)
		&& (GetAsyncKeyState(VK_UP) & 0x8000))
	{
		Util::GetInstance().PrintLog(L"UR");
		return;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)
		&& (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		Util::GetInstance().PrintLog(L"DR");
		return;
	}


	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Util::GetInstance().PrintLog(L"LL");
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		Util::GetInstance().PrintLog(L"UU");
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Util::GetInstance().PrintLog(L"RR");
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
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