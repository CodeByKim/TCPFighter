#include "TCPFighter.h"
#include "Util.h"
#include "Game.h"
#include "Resources.h"
#include "Sprite.h"
#include "InputComponent.h"
#include "GameObjectComponent.h"
#include "RenderComponent.h"
#include "Player.h"

TCPFighter::TCPFighter(HINSTANCE hInstance, int nCmdShow)
	: Game(hInstance, nCmdShow)
    , mBackgroundSprite(nullptr)
    , mMyPlayer(nullptr)
{
    mRender = (RenderComponent*)GetComponent(eComponentType::Render);

    SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    LoadAllSprites();
    RegisterInputHandlers();

    if (!Connect(SERVER_IP, SERVER_PORT))
    {
        if (WSAGetLastError() != WSAEWOULDBLOCK)
        {
            MessageBox(mhWnd, L"Connect()", L"Error", 0);
            return;
        }
    }

    CreateGameObject();
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

void TCPFighter::RegisterInputHandlers()
{
    InputComponent* inputComponent = (InputComponent*)GetComponent(eComponentType::Input);

    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_LL, [this]() {        
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_LL);
        });
    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_LU, [this]() {
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_LU);
        });
    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_UU, [this]() {
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_UU);
        });
    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_RU, [this]() {
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_RU);
        });
    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_RR, [this]() {
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_RR);
        });
    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_RD, [this]() {
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_RD);
        });
    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_DD, [this]() {
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_DD);
        });
    inputComponent->RegisterInputHandler(dfPACKET_MOVE_DIR_LD, [this]() {
        mMyPlayer->MovePlayer(dfPACKET_MOVE_DIR_LD);
        });
    inputComponent->RegisterInputHandler(dfPACKET_ATTACK_1, [this]() {
        mMyPlayer->Attack(dfPACKET_ATTACK_1);
        });
    inputComponent->RegisterInputHandler(dfPACKET_ATTACK_2, [this]() {
        mMyPlayer->Attack(dfPACKET_ATTACK_2);
        });
    inputComponent->RegisterInputHandler(dfPACKET_ATTACK_3, [this]() {
        mMyPlayer->Attack(dfPACKET_ATTACK_3);
        });
}

void TCPFighter::CreateGameObject()
{
    Position2D mapPivot = { 0, 0 };
    Sprite* mapSprite = Resources::GetInstance().CreateSprite(L"Map", mapPivot);
    mBackgroundSprite.reset(mapSprite);

    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    mMyPlayer = std::make_shared<Player>(Position2D{ 200, 200 }, -1);
    objectComponent->RegisterObject(mMyPlayer);
}