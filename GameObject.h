#pragma once
#include "CommonLibrary.h"

class Graphics;

class GameObject
{
public:
	GameObject(Position2D position, int id);

	virtual void OnFrameUpdate() = 0;
	virtual void OnRender(Graphics& graphics) = 0;

	int GetID();
	Position2D& GetPosition()
	{
		return mPosition;
	}
protected:
	Position2D mPosition;
	int mID;
};

