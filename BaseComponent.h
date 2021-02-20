#pragma once
#include "CommonLibrary.h"

enum class eComponentType
{
	GameObject,
	Render
};

class GameObject;

class BaseComponent
{
public:
	virtual void Update(std::vector<std::unique_ptr<GameObject>>& objects) = 0;
	virtual eComponentType GetType() = 0;
private:

};

