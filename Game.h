#pragma once
#include "CommonLibrary.h"
#include "NetworkClient.h"

class Game : public NetworkClient
{
public:
	Game(HINSTANCE hInstance, int nCmdShow);
	~Game();

protected:
	void FrameUpdate() override;

private:

};

