#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"

class GameObject;
class Game;

class GameObjectComponent : public BaseComponent
{
public:
	GameObjectComponent(Game& game);

	void Update() override;
	eComponentType GetType() override;
	void RegisterObject(std::shared_ptr<GameObject> object);
	void DeleteObject(std::shared_ptr<GameObject> object);

	std::vector<std::shared_ptr<GameObject>>& GetObjects();

private:
	std::vector<std::shared_ptr<GameObject>> mGameObjects;
};

