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
	void SC_MOVE_START(Packet* packet);
	void SC_MOVE_STOP(Packet* packet);
	void SC_ATTACK1(Packet* packet);
	void SC_ATTACK2(Packet* packet);
	void SC_ATTACK3(Packet* packet);
	void SC_DAMAGE(Packet* packet);

	std::unique_ptr<Sprite> mBackgroundSprite;
	RenderComponent* mRender;

	std::shared_ptr<Player> mMyPlayer;
	std::unordered_map<int, std::shared_ptr<Player>> mOtherPlayers;
};