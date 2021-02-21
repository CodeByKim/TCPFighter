#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"

class TCPFighter;

#pragma region Commands...
class ICommand
{
public:
	virtual void Execute(TCPFighter& game) = 0;
};

class UpKeyCommand : public ICommand
{
public:
	void Execute(TCPFighter& game) override;
};

class DownKeyCommand : public ICommand
{
public:
	void Execute(TCPFighter& game) override;
};

class LeftKeyCommand : public ICommand
{
public:
	void Execute(TCPFighter& game) override;
};

class RightKeyCommand : public ICommand
{
public:
	void Execute(TCPFighter& game) override;
};

class Attack1Command : public ICommand
{
public:
	void Execute(TCPFighter& game) override;
};

class Attack2Command : public ICommand
{
public:
	void Execute(TCPFighter& game) override;
};

class Attack3Command : public ICommand
{
public:
	void Execute(TCPFighter& game) override;
};
#pragma endregion

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

