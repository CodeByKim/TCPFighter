#include "TCPFighter.h"
#include "Util.h"
#include "Game.h"
#include "Resources.h"
#include "Sprite.h"
#include "InputComponent.h"
#include "GameObjectComponent.h"
#include "RenderComponent.h"
#include "Player.h"
//#include "Packet.h"
#include "NetPacket.h"

TCPFighter::TCPFighter(HINSTANCE hInstance, int nCmdShow)
	: Game(hInstance, nCmdShow)
    , mBackgroundSprite(nullptr)
    , mMyPlayer(nullptr)
    , mIsGameOver(false)
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

void TCPFighter::SendPacket(std::shared_ptr<NetPacket> packet)
{
    NetworkClient::SendPacket(packet);
}

void TCPFighter::FrameUpdate()
{   
    Game::FrameUpdate();

    mRender->DrawSprite(mBackgroundSprite.get(), Position2D{ 0,0 });    
}

void TCPFighter::OnConnect()
{
    Util::GetInstance().PrintLog(L"On Connect...");
}

void TCPFighter::OnReceive(NetPacket* packet)
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
        case dfPACKET_SC_ATTACK2:
            SC_ATTACK2(packet);
            break;
        case dfPACKET_SC_ATTACK3:
            SC_ATTACK3(packet);
            break;
        case dfPACKET_SC_DAMAGE:
            SC_DAMAGE(packet);
            break;
        case dfPACKET_SC_DELETE_CHARACTER:
            SC_DELETE_CHARACTER(packet);
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

void TCPFighter::SC_CREATE_MY_CHARACTER(NetPacket* packet)
{
    int id;
    char direction;
    short x;
    short y;
    char hp;
    *packet >> id >> direction >> x >> y >> hp;

    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    mMyPlayer = std::make_shared<Player>(
        id, 
        Position2D{ x, y }, 
        direction, 
        hp, 
        *this);

    objectComponent->RegisterObject(mMyPlayer);
}

void TCPFighter::SC_CREATE_OTHER_CHARACTER(NetPacket* packet)
{
    int id;
    char direction;
    short x;
    short y;
    char hp;
    *packet >> id >> direction >> x >> y >> hp;

    GameObjectComponent* objectComponent = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
    auto otherPlayer = std::make_shared<Player>(
        id,
        Position2D{ x, y },
        direction,
        hp,
        *this);

    otherPlayer->SetRemote();
    objectComponent->RegisterObject(otherPlayer);
    mOtherPlayers.insert(std::make_pair(id, otherPlayer));
}

void TCPFighter::SC_MOVE_START(NetPacket* packet)
{
    int id;
    char direction;
    short x;
    short y;
    *packet >> id >> direction >> x >> y;

    if (mOtherPlayers.find(id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[id]->RemoteMoveStart(direction, x, y);
}

void TCPFighter::SC_MOVE_STOP(NetPacket* packet)
{
    int id;
    char direction;
    short x;
    short y;
    *packet >> id >> direction >> x >> y;

    if (mOtherPlayers.find(id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[id]->RemoteMoveStop(direction, x, y);
}

void TCPFighter::SC_ATTACK1(NetPacket* packet)
{
    int id;
    char direction;
    short x;
    short y;
    *packet >> id >> direction >> x >> y;

    if (mOtherPlayers.find(id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[id]->RemoteAttack1(direction, x, y);
}

void TCPFighter::SC_ATTACK2(NetPacket* packet)
{
    int id;
    char direction;
    short x;
    short y;
    *packet >> id >> direction >> x >> y;

    if (mOtherPlayers.find(id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[id]->RemoteAttack2(direction, x, y);
}

void TCPFighter::SC_ATTACK3(NetPacket* packet)
{
    int id;
    char direction;
    short x;
    short y;
    *packet >> id >> direction >> x >> y;

    if (mOtherPlayers.find(id) == mOtherPlayers.end())
    {
        Util::GetInstance().PrintError(L"not found remote player");
        return;
    }

    mOtherPlayers[id]->RemoteAttack3(direction, x, y);
}

void TCPFighter::SC_DAMAGE(NetPacket* packet)
{
    int attackID;
    int hitID;
    char damage;    
    *packet >> attackID >> hitID >> damage;
        
    if (mOtherPlayers.find(hitID) != mOtherPlayers.end())
    {
        mOtherPlayers[hitID]->Hit(damage);
    }    
    else
    {
        mMyPlayer->Hit(damage);
    }    
}

void TCPFighter::SC_DELETE_CHARACTER(NetPacket* packet)
{
    int id;
    *packet >> id;

    if (id == mMyPlayer->GetID())
    {
        //³»°¡ Á×¾î¹ö·È³×...
        mIsGameOver = true;        
        return;
    }

    if (mOtherPlayers.find(id) != mOtherPlayers.end())
    {        
        GameObjectComponent* component = (GameObjectComponent*)GetComponent(eComponentType::GameObject);
        component->DeleteObject(mOtherPlayers[id]);
        
        mOtherPlayers.erase(mOtherPlayers.find(id));
    }
}