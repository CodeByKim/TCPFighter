#pragma once
#include "CommonLibrary.h"
#include "Game.h"
#include "Sprite.h"

class RenderComponent;
class Player;
class Packet;

class TCPFighter : public Game
{
public:
	TCPFighter(HINSTANCE hInstance, int nCmdShow);
	~TCPFighter();

	void SendPacket(std::shared_ptr<Packet> packet);

protected:
	void FrameUpdate() override;
	
	void OnConnect() override;
	void OnReceive(Packet* packet) override;
	void OnDisconnect() override;

private:
	void LoadAllSprites();
	void RegisterInputHandlers();
	void CreateGameObject();

	void SC_CREATE_MY_CHARACTER(Packet* packet);
	void SC_CREATE_OTHER_CHARACTER(Packet* packet);

	std::unique_ptr<Sprite> mBackgroundSprite;
	RenderComponent* mRender;

	std::shared_ptr<Player> mMyPlayer;
};