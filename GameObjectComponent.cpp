#include "GameObjectComponent.h"
#include "Util.h"

void GameObjectComponent::Update(std::vector<std::unique_ptr<GameObject>>& objects)
{
	Util::GetInstance().PrintLog(L"Update GameObjectComponent...");
}
