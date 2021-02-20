#pragma once
#include "CommonLibrary.h"

class GameObject;

class BaseComponent
{
public:
	virtual void Update(std::vector<std::unique_ptr<GameObject>>& objects) = 0;
private:

};

