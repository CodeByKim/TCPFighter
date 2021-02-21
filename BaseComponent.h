#pragma once
#include "CommonLibrary.h"

class Game;

enum class eComponentType
{
	GameObject,
	Render
};

class GameObject;

class BaseComponent
{
public:
	BaseComponent(Game& game);

	virtual void Update() = 0;
	virtual eComponentType GetType() = 0;

protected:
	Game& mGame;

private:

};

