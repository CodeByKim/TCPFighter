#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"

class GameObject;

class GameObjectComponent : public BaseComponent
{
public:
	void Update(std::vector<std::unique_ptr<GameObject>>& objects) override;
};

