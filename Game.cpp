#include "Game.h"
#include "NetworkClient.h"
#include "Util.h"
#include "BaseComponent.h"
#include "InputComponent.h"
#include "GameObjectComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Packet.h"

Game::Game(HINSTANCE hInstance, int nCmdShow)
	: NetworkClient(hInstance, nCmdShow)    
{    
    CreateGameComponents();
}

Game::~Game()
{    
    mComponents.clear();
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

std::vector<std::shared_ptr<GameObject>>& Game::GetGameObjects()
{
    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    return objectComponent->GetObjects();
}

void Game::FrameUpdate()
{	
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < mComponents.size(); i++)
    {
        mComponents[i]->Update();        
    }

    //OnFrameUpdate();
    std::chrono::nanoseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    float spent = elapsed.count() / 1000000.0f;    
    Sleep(20 - spent);
    
    ShowLogAtWindowTitle(L"Logic Frame", CalcFps(start));
}

void Game::CreateGameComponents()
{
    mComponents.clear();

    mComponents.push_back(std::make_unique<InputComponent>(*this));
    mComponents.push_back(std::make_unique<GameObjectComponent>(*this));
    mComponents.push_back(std::make_unique<RenderComponent>(*this, mhWnd, mScreenSize));
}

int Game::CalcFps(std::chrono::high_resolution_clock::time_point startTime)
{
    std::chrono::nanoseconds end = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime);
    float fps = 1000.0f / (end.count() / 1000000.0f);

    mFpsQueue.push_back(fps);

    if (mFpsQueue.size() > 50)
    {
        float sum = 0;
        for (size_t i = 0; i < mFpsQueue.size(); i++)
        {
            sum += mFpsQueue[i];
        }

        fps = sum / mFpsQueue.size();
        mFpsQueue.erase(mFpsQueue.begin());
    }

    return (int)fps;
}

void Game::ShowLogAtWindowTitle(std::wstring_view message, int code)
{
    WCHAR str[32];
    wsprintf(str, L"%s : %d\n", message.data(), code);
    SetWindowText(mhWnd, str);
}