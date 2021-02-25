#pragma once
#include "CommonLibrary.h"
#include "Game.h"
#include "Sprite.h"

class RenderComponent;
class Player;
class NetPacket;

class TCPFighter : public Game
{
public:
	TCPFighter(HINSTANCE hInstance, int nCmdShow);
	~TCPFighter();

	void SendPacket(std::shared_ptr<NetPacket> packet);

protected:
	void FrameUpdate() override;
	
	void OnConnect() override;
	void OnReceive(NetPacket* packet) override;
	void OnDisconnect() override;

private:
	void LoadAllSprites();
	void RegisterInputHandlers();
	void CreateGameObject();

	void SC_CREATE_MY_CHARACTER(NetPacket* packet);
	void SC_CREATE_OTHER_CHARACTER(NetPacket* packet);
	void SC_MOVE_START(NetPacket* packet);
	void SC_MOVE_STOP(NetPacket* packet);
	void SC_ATTACK1(NetPacket* packet);
	void SC_ATTACK2(NetPacket* packet);
	void SC_ATTACK3(NetPacket* packet);
	void SC_DAMAGE(NetPacket* packet);
	void SC_DELETE_CHARACTER(NetPacket* packet);

	std::unique_ptr<Sprite> mBackgroundSprite;
	RenderComponent* mRender;

	std::shared_ptr<Player> mMyPlayer;
	std::unordered_map<int, std::shared_ptr<Player>> mOtherPlayers;

	bool mIsGameOver;
};