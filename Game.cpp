#include "Game.h"
#include "NetworkClient.h"
#include "Util.h"

Game::Game(HINSTANCE hInstance, int nCmdShow)
	: NetworkClient(hInstance, nCmdShow)
{

}

Game::~Game()
{

}

void Game::FrameUpdate()
{
	Util::GetInstance().PrintLog(L"Frame Update...");
}