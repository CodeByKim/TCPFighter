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

	BaseComponent* GetComponent(eComponentType type);
	//void SetScreenSize(int screenWidth, int screenHeight);

protected:
	void FrameUpdate() override;

private:	
	void CreateGameComponents();	

	std::vector<std::unique_ptr<GameObject>> mGameObjects;
	std::vector<std::unique_ptr<BaseComponent>> mComponents;	
};

