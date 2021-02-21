#pragma once
#include "CommonLibrary.h"
#include "NetworkClient.h"
#include "BaseComponent.h"

class Sprite;
class GameObject;

class Game : public NetworkClient
{
public:
	Game(HINSTANCE hInstance, int nCmdShow);
	~Game();

	std::vector<std::shared_ptr<GameObject>>& GetGameObjects();
	BaseComponent* GetComponent(eComponentType type);	
	
protected:
	void FrameUpdate() override;

private:	
	void CreateGameComponents();	
	
	std::vector<std::unique_ptr<BaseComponent>> mComponents;	
};

