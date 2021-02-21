#pragma once
#include "CommonLibrary.h"
#include "Game.h"
#include "Sprite.h"

class RenderComponent;
class Player;

class TCPFighter : public Game
{
public:
	TCPFighter(HINSTANCE hInstance, int nCmdShow);
	~TCPFighter();

	void MovePlayer(int dir);

protected:
	void FrameUpdate() override;

private:
	void LoadAllSprites();

	std::unique_ptr<Sprite> mBackgroundSprite;
	RenderComponent* mRender;

	std::shared_ptr<Player> mMyPlayer;
};