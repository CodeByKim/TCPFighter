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
{    
    CreateGameComponents();
}

Game::~Game()
{    
    mComponents.clear();
}

void Game::FrameUpdate()
{
	Util::GetInstance().PrintLog(L"Game FrameUpdate...");

    for (size_t i = 0; i < mComponents.size(); i++)
    {
        mComponents[i]->Update();        
    }

    //임시로 프레임 맞춤
    Sleep(20);
}

void Game::CreateGameComponents()
{
    mComponents.clear();
    mComponents.push_back(std::make_unique<GameObjectComponent>(*this));
    mComponents.push_back(std::make_unique<RenderComponent>(*this, mhWnd, mScreenSize));
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