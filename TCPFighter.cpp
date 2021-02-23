#include "TCPFighter.h"
#include "Util.h"
#include "Game.h"
#include "Resources.h"
#include "Sprite.h"
#include "InputComponent.h"
#include "GameObjectComponent.h"
#include "RenderComponent.h"
#include "Player.h"
#include "Packet.h"

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

void TCPFighter::SendPacket(std::shared_ptr<Packet> packet)
{
    NetworkClient::SendPacket(packet);
}

void TCPFighter::FrameUpdate()
{
    mRender->DrawSprite(mBackgroundSprite.get(), Position2D{ 0,0 });

    Game::FrameUpdate();
}

void TCPFighter::OnConnect()
{
    Util::GetInstance().PrintLog(L"On Connect...");
}

void TCPFighter::OnReceive(Packet* packet)
{
    switch (packet->header.protocol)
    {
        case dfPACKET_SC_CREATE_MY_CHARACTER:
            SC_CREATE_MY_CHARACTER(packet);
            break;
        case dfPACKET_SC_CREATE_OTHER_CHARACTER:
            SC_CREATE_OTHER_CHARACTER(packet);
            break;
        case dfPACKET_SC_MOVE_START:
            SC_MOVE_START(packet);
            break;
        case dfPACKET_SC_MOVE_STOP:
            SC_MOVE_STOP(packet);
            break;
        case dfPACKET_SC_ATTACK1:
            SC_ATTACK1(packet);
            break;
    }
}

void TCPFighter::OnDisconnect()
{

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
    inputComponent->RegisterInputHandler(dfPACKET_CS_ATTACK1, [this]() {
        mMyPlayer->Attack(dfPACKET_CS_ATTACK1);
        });
    inputComponent->RegisterInputHandler(dfPACKET_CS_ATTACK2, [this]() {
        mMyPlayer->Attack(dfPACKET_CS_ATTACK2);
        });
    inputComponent->RegisterInputHandler(dfPACKET_CS_ATTACK3, [this]() {
        mMyPlayer->Attack(dfPACKET_CS_ATTACK3);
        });
}

void TCPFighter::CreateGameObject()
{
    Position2D mapPivot = { 0, 0 };
    Sprite* mapSprite = Resources::GetInstance().CreateSprite(L"Map", mapPivot);
    mBackgroundSprite.reset(mapSprite);    
}

void TCPFighter::SC_CREATE_MY_CHARACTER(Packet* packet)
{
    PACKET_SC_CREATE_MY_CHARACTER data;
    data.Deserialize(packet);

    wchar_t str[256];
    wsprintf(str, L"%s : %d, %d, %d, %d, %d",
        L"dfPACKET_SC_CREATE_MY_CHARACTER",
        data.id,
        data.direction,
        data.x,
        data.y,
        data.hp);
    Util::GetInstance().PrintLog(str);

    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    mMyPlayer = std::make_shared<Player>(
        data.id, 
        Position2D{ data.x, data.y }, 
        data.direction, 
        data.hp, 
        *this);

    objectComponent->RegisterObject(mMyPlayer);
}

void TCPFighter::SC_CREATE_OTHER_CHARACTER(Packet* packet)
{
    PACKET_SC_CREATE_OTHER_CHARACTER data;
    data.Deserialize(packet);

    wchar_t str[256];
    wsprintf(str, L"%s : %d, %d, %d, %d, %d",
        L"dfPACKET_SC_CREATE_OTHER_CHARACTER",
        data.id,
        data.direction,
        data.x,
        data.y,
        data.hp);
    Util::GetInstance().PrintLog(str);

    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    auto otherPlayer = std::make_shared<Player>(
        data.id,
        Position2D{ data.x, data.y },
        data.direction,
        data.hp,
        *this);

    otherPlayer->SetRemote();
    objectComponent->RegisterObject(otherPlayer);
    mOtherPlayers.insert(std::make_pair(data.id, otherPlayer));
}

void TCPFighter::SC_MOVE_START(Packet* packet)
{
    PACKET_SC_MOVE_START data;
    data.Deserialize(packet);

    if (mOtherPlayers.find(data.id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[data.id]->RemoteMoveStart(data.direction, data.x, data.y);
}

void TCPFighter::SC_MOVE_STOP(Packet* packet)
{
    PACKET_SC_MOVE_STOP data;
    data.Deserialize(packet);

    if (mOtherPlayers.find(data.id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[data.id]->RemoteMoveStop(data.direction, data.x, data.y);
}

void TCPFighter::SC_ATTACK1(Packet* packet)
{
    PACKET_SC_ATTACK1 data;
    data.Deserialize(packet);

    if (mOtherPlayers.find(data.id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[data.id]->RemoteAttack1(data.direction, data.x, data.y);
}