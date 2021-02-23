#include "InputComponent.h"
#include "Game.h"
#include "Util.h"

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
	if (!mGame.IsFocus())
	{
		return;
	}

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
		mInputHandlers[dfPACKET_MOVE_DIR_LU]();
		return;
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000)
		&& (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{		
		mInputHandlers[dfPACKET_MOVE_DIR_LD]();
		return;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)
		&& (GetAsyncKeyState(VK_UP) & 0x8000))
	{		
		mInputHandlers[dfPACKET_MOVE_DIR_RU]();
		return;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)
		&& (GetAsyncKeyState(VK_DOWN) & 0x8000))
	{		
		mInputHandlers[dfPACKET_MOVE_DIR_RD]();
		return;
	}


	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{		
		mInputHandlers[dfPACKET_MOVE_DIR_LL]();
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{		
		mInputHandlers[dfPACKET_MOVE_DIR_UU]();
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{		
		mInputHandlers[dfPACKET_MOVE_DIR_RR]();
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{		
		mInputHandlers[dfPACKET_MOVE_DIR_DD]();
	}
}

void InputComponent::HandleAttackInput()
{
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		mInputHandlers[dfPACKET_ATTACK_1]();
	}

	if (GetAsyncKeyState('X') & 0x8000)
	{
		mInputHandlers[dfPACKET_ATTACK_2]();
	}

	if (GetAsyncKeyState('C') & 0x8000)
	{
		mInputHandlers[dfPACKET_ATTACK_3]();
	}
}