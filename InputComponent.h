#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"

class TCPFighter;

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

class InputComponent : public BaseComponent
{
public:
	InputComponent(Game& game);

	void Update() override;
	eComponentType GetType() override;

private:
	void HandleMoveInput();
	void HandleAttackInput();
};

