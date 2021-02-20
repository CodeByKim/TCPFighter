#pragma once
#include "CommonLibrary.h"
#include "NetworkClient.h"

class BaseComponent;
class GameObject;

class Game : public NetworkClient
{
public:
	Game(HINSTANCE hInstance, int nCmdShow);
	~Game();

protected:
	void FrameUpdate() override;

private:
	void SetScreenSize();
	void CreateGameComponents();

	std::vector<std::unique_ptr<GameObject>> mGameObjects;
	std::vector<std::unique_ptr<BaseComponent>> mComponents;
};

