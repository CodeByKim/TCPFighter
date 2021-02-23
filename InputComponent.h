#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"

class TCPFighter;

class InputComponent : public BaseComponent
{
public:
	InputComponent(Game& game);

	void RegisterInputHandler(int message, std::function<void()> func);

	void Update() override;
	eComponentType GetType() override;

private:	
	void HandleMoveInput();
	void HandleAttackInput();

	std::unordered_map<int, std::function<void()>> mInputHandlers;
};

