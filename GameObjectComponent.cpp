#include "GameObjectComponent.h"
#include "Util.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(Game& game)
	: BaseComponent(game)
{

}

void GameObjectComponent::Update()
{
	Util::GetInstance().PrintLog(L"Update GameObjectComponent...");

	for (size_t i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->OnFrameUpdate();
	}
}

eComponentType GameObjectComponent::GetType()
{
	return eComponentType::GameObject;
}

std::vector<std::shared_ptr<GameObject>>& GameObjectComponent::GetObjects()
{
	return mGameObjects;
}

void GameObjectComponent::RegisterObject(std::shared_ptr<GameObject> object)
{
	mGameObjects.push_back(object);
}