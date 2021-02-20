#include "RenderComponent.h"
#include "Util.h"

void RenderComponent::DrawSprite(Sprite* sprite, int x, int y)
{

}

void RenderComponent::Update(std::vector<std::unique_ptr<GameObject>>& objects)
{
	Util::GetInstance().PrintLog(L"Update RenderComponent...");
}

eComponentType RenderComponent::GetType()
{
	return eComponentType::Render;
}