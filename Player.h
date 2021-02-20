#pragma once
#include "CommonLibrary.h"
#include "GameObject.h"

class Graphics;

class Player : public GameObject
{
public:
	void OnFrameUpdate() override;
	void OnRender(Graphics& graphics) override;

private:

};

