#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"

class GameObject;
class Sprite;

class RenderComponent : public BaseComponent
{
public:
	void DrawSprite(Sprite* sprite, int x, int y);

	void Update(std::vector<std::unique_ptr<GameObject>>& objects) override;
	eComponentType GetType() override;
};

