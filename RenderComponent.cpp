#include "RenderComponent.h"
#include "Util.h"
#include "GameObject.h"

RenderComponent::RenderComponent(HWND hWnd, ScreenSize screenSize)
	: mGraphics(hWnd, screenSize)
{	
	
}

RenderComponent::~RenderComponent()
{
	
}

void RenderComponent::DrawSprite(Sprite* sprite, Position2D pos)
{
	mGraphics.Draw(sprite, pos);
}

void RenderComponent::Update(std::vector<std::unique_ptr<GameObject>>& objects)
{
	Util::GetInstance().PrintLog(L"Update RenderComponent...");

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