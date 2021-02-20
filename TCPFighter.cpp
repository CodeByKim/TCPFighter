#include "TCPFighter.h"
#include "Util.h"
#include "Game.h"
#include "Resources.h"
#include "Sprite.h"
#include "RenderComponent.h"

TCPFighter::TCPFighter(HINSTANCE hInstance, int nCmdShow)
	: Game(hInstance, nCmdShow)
    , mBackgroundSprite(nullptr)
{
    LoadAllSprites();

    Sprite* mapSprite = Resources::GetInstance().CreateSprite(L"Map.bmp", 0, 0);
    mBackgroundSprite.reset(mapSprite);

    mRender = (RenderComponent*)GetComponent(eComponentType::Render);
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

    Resources::GetInstance().LoadSprite(L"Map.bmp", mapPivot);

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