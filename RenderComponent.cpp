#include "RenderComponent.h"
#include "Util.h"
#include "GameObject.h"
#include "Game.h"

RenderComponent::RenderComponent(Game& game, HWND hWnd, ScreenSize screenSize)
	: BaseComponent(game)
	, mGraphics(hWnd, screenSize)	
{	
	
}

RenderComponent::~RenderComponent()
{
	
}

void RenderComponent::DrawSprite(Sprite* sprite, Position2D pos)
{
	mGraphics.Draw(sprite, pos);
}

void RenderComponent::Update()
{	
	auto objects = mGame.GetGameObjects();
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->OnRender(mGraphics);
	}

	mGraphics.Render();	
}

eComponentType RenderComponent::GetType()
{
	return eComponentType::Render;
}