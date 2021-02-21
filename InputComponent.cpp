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
#pragma endregion

InputComponent::InputComponent(Game& game)
	: BaseComponent(game)
{

}

void InputComponent::RegisterInputHandler(int message, std::function<void()> func)
{
	if (mInputHandlers.find(message) != mInputHandlers.end())
	{
		Util::GetInstance().ShowMessageBox(L"Error RegisterInputHandler()");
		return;
	}

	mInputHandlers.insert(std::make_pair(message, func));
}

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
		//Util::GetInstance().PrintLog(L"UL");
		mInputHandlers[dfPACKET_MOVE_DIR_LU]();
		return;
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)
		&& (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		//Util::GetInstance().PrintLog(L"DL");
		mInputHandlers[dfPACKET_MOVE_DIR_LD]();
		return;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)
		&& (GetAsyncKeyState(VK_UP) & 0x8000))
	{
		//Util::GetInstance().PrintLog(L"UR");
		mInputHandlers[dfPACKET_MOVE_DIR_RU]();
		return;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)
		&& (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		//Util::GetInstance().PrintLog(L"DR");
		mInputHandlers[dfPACKET_MOVE_DIR_RD]();
		return;
	}


	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		//Util::GetInstance().PrintLog(L"LL");
		mInputHandlers[dfPACKET_MOVE_DIR_LL]();
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//Util::GetInstance().PrintLog(L"UU");
		mInputHandlers[dfPACKET_MOVE_DIR_UU]();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		//Util::GetInstance().PrintLog(L"RR");
		mInputHandlers[dfPACKET_MOVE_DIR_RR]();
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		//Util::GetInstance().PrintLog(L"DD");
		mInputHandlers[dfPACKET_MOVE_DIR_DD]();
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