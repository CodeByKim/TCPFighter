#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"

class GameObject;

class RenderComponent : public BaseComponent
{
public:
	void Update(std::vector<std::unique_ptr<GameObject>>& objects) override;
};

