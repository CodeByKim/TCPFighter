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
    , mMyPlayer(nullptr)
{
    SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    LoadAllSprites();

    Position2D mapPivot = { 0, 0 };    
    Sprite* mapSprite = Resources::GetInstance().CreateSprite(L"Map", mapPivot);
    mBackgroundSprite.reset(mapSprite);

    mRender = (RenderComponent*)GetComponent(eComponentType::Render);
    
    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    mMyPlayer = std::make_shared<Player>(Position2D{ 200, 200 }, -1);
    objectComponent->RegisterObject(mMyPlayer);
}

TCPFighter::~TCPFighter()
{
    
}

void TCPFighter::FrameUpdate()
{
    mRender->DrawSprite(mBackgroundSprite.get(), Position2D{ 0,0 });

    Game::FrameUpdate();    
}

void TCPFighter::LoadAllSprites()
{   
    Resources::GetInstance().LoadSprite(L"Map");
    
    Resources::GetInstance().LoadSpriteAnimation(L"Stand_L");
    Resources::GetInstance().LoadSpriteAnimation(L"Stand_R");

    Resources::GetInstance().LoadSpriteAnimation(L"Move_L");
    Resources::GetInstance().LoadSpriteAnimation(L"Move_R");

    Resources::GetInstance().LoadSpriteAnimation(L"Attack1_L");
    Resources::GetInstance().LoadSpriteAnimation(L"Attack1_R");
    Resources::GetInstance().LoadSpriteAnimation(L"Attack2_L");
    Resources::GetInstance().LoadSpriteAnimation(L"Attack2_R");
    Resources::GetInstance().LoadSpriteAnimation(L"Attack3_L");
    Resources::GetInstance().LoadSpriteAnimation(L"Attack3_R");
}