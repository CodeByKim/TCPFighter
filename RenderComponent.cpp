#include "RenderComponent.h"
#include "Util.h"

void RenderComponent::Update(std::vector<std::unique_ptr<GameObject>>& objects)
{
	Util::GetInstance().PrintLog(L"Update RenderComponent...");
}