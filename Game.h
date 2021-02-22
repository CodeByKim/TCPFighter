#pragma once
#include "CommonLibrary.h"
#include "NetworkClient.h"
#include "BaseComponent.h"

class Sprite;
class GameObject;
class Packet;

class Game : public NetworkClient
{
public:
	Game(HINSTANCE hInstance, int nCmdShow);
	~Game();

	std::vector<std::shared_ptr<GameObject>>& GetGameObjects();
	BaseComponent* GetComponent(eComponentType type);	
	
protected:
	void FrameUpdate() override;

	void OnConnect() override;
	void OnReceive(Packet* packet) override;
	void OnDisconnect() override;

private:	
	void CreateGameComponents();	
	int CalcFps(std::chrono::high_resolution_clock::time_point startTime);
	void ShowLogAtWindowTitle(std::wstring_view message, int code);

	std::vector<std::unique_ptr<BaseComponent>> mComponents;
	std::vector<float> mFpsQueue;
};

