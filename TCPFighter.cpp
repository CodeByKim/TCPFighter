#include "TCPFighter.h"
#include "Util.h"
#include "Game.h"
#include "Resources.h"
#include "Sprite.h"
#include "GameObjectComponent.h"
#include "RenderComponent.h"
#include "Player.h"

TCPFighter::TCPFighter(HINSTANCE hInstance, int nCmdShow)
	: Game(hInstance, nCmdShow)
    , mBackgroundSprite(nullptr)
{
    SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    LoadAllSprites();

    Sprite* mapSprite = Resources::GetInstance().CreateSprite(L"Map");
    mBackgroundSprite.reset(mapSprite);

    mRender = (RenderComponent*)GetComponent(eComponentType::Render);
    
    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    auto player = std::make_shared<Player>(Position2D{ 100, 100 }, -1);
    objectComponent->RegisterObject(player);
}

TCPFighter::~TCPFighter()
{
    
}

void TCPFighter::FrameUpdate()
{
    mRender->DrawSprite(mBackgroundSprite.get(), Position2D{ 0,0 });

    Game::FrameUpdate();

    Util::GetInstance().PrintLog(L"TCPFighter FrameUpdate...");
}

void TCPFighter::LoadAllSprites()
{
    Position2D mapPivot = { 0, 0 };
    Position2D pivot = { 71, 90 };

    Resources::GetInstance().LoadSprite(L"Map", mapPivot);
    
    Resources::GetInstance().LoadSpriteAnimation(L"Stand_L", pivot);
    Resources::GetInstance().LoadSpriteAnimation(L"Stand_R", pivot);

    Resources::GetInstance().LoadSpriteAnimation(L"Move_L", pivot);
    Resources::GetInstance().LoadSpriteAnimation(L"Move_R", pivot);

    Resources::GetInstance().LoadSpriteAnimation(L"Attack1_L", pivot);
    Resources::GetInstance().LoadSpriteAnimation(L"Attack1_R", pivot);
    Resources::GetInstance().LoadSpriteAnimation(L"Attack2_L", pivot);
    Resources::GetInstance().LoadSpriteAnimation(L"Attack2_R", pivot);
    Resources::GetInstance().LoadSpriteAnimation(L"Attack3_L", pivot);
    Resources::GetInstance().LoadSpriteAnimation(L"Attack3_R", pivot);
}