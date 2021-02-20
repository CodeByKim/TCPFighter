#include "Game.h"
#include "NetworkClient.h"
#include "Util.h"
#include "BaseComponent.h"
#include "GameObjectComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Sprite.h"

Game::Game(HINSTANCE hInstance, int nCmdShow)
	: NetworkClient(hInstance, nCmdShow)
    , mScreenSize {SCREEN_WIDTH, SCREEN_HEIGHT}
{    
    CreateGameComponents();
}

Game::~Game()
{

}

void Game::FrameUpdate()
{
	Util::GetInstance().PrintLog(L"Game FrameUpdate...");

    for (size_t i = 0; i < mComponents.size(); i++)
    {
        mComponents[i]->Update(mGameObjects);        
    }
}

void Game::SetScreenSize(int screenWidth, int screenHeight)
{
    mScreenSize.width = screenWidth;
    mScreenSize.height = screenHeight;

    RECT rectWindow = { 0, 0, screenWidth, screenHeight };
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
    mComponents.push_back(std::make_unique<RenderComponent>(mhWnd, mScreenSize));
}

BaseComponent* Game::GetComponent(eComponentType type)
{
    for (size_t i = 0; i < mComponents.size(); i++)
    {
        if (mComponents[i]->GetType() == type)
        {
            return mComponents[i].get();
        }
    }

    return nullptr;
}