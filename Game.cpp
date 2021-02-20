#include "Game.h"
#include "NetworkClient.h"
#include "Util.h"
#include "GameObjectComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"

Game::Game(HINSTANCE hInstance, int nCmdShow)
	: NetworkClient(hInstance, nCmdShow)
{
    SetScreenSize();
    CreateGameComponents();
}

Game::~Game()
{

}

void Game::FrameUpdate()
{
	Util::GetInstance().PrintLog(L"Frame Update...");

    for (int i = 0; i < mComponents.size(); i++)
    {
        mComponents[i]->Update(mGameObjects);        
    }
}

void Game::SetScreenSize()
{
    RECT rectWindow = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    AdjustWindowRect(&rectWindow, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(mhWnd,
        HWND_TOPMOST,
        100,
        100,
        rectWindow.right - rectWindow.left,
        rectWindow.bottom - rectWindow.top,
        SWP_NOMOVE | SWP_NOZORDER);
}

void Game::CreateGameComponents()
{
    mComponents.clear();
    mComponents.push_back(std::make_unique<GameObjectComponent>());
    mComponents.push_back(std::make_unique<RenderComponent>());
}