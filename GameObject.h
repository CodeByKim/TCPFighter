#pragma once
#include "CommonLibrary.h"

class Graphics;

class GameObject
{
public:
	virtual void OnFrameUpdate() = 0;
	virtual void OnRender(Graphics& graphics) = 0;

private:
};

