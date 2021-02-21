#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"
#include "Graphics.h"

class GameObject;
class Sprite;
class Game;

class RenderComponent : public BaseComponent
{
public:
	RenderComponent(Game& game, HWND hWnd, ScreenSize screenSize);
	~RenderComponent();

	void DrawSprite(Sprite* sprite, Position2D pos);

	void Update() override;
	eComponentType GetType() override;

private:	
	Graphics mGraphics;	
};

