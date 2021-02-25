#include "NetPacket.h"

PacketException::PacketException(ePacketOperationType type, int packetSize, int trySize)
    : mType(type)
    , mPacketSize(packetSize)
    , mTrySize(trySize)
{    
}

PacketException::~PacketException()
{    
}

char const* PacketException::what() const
{            
    return "Packet Exception";
}

std::string PacketException::Log()
{
    std::ostringstream os;
    os << "[PacketException] =>"; 
    os << " Type : " << ((mType == ePacketOperationType::GetData) ? "GutData" : "PutData");
    os << ", PacketSize : " << mPacketSize;
    os << ", TrySize : " << mTrySize;

    return os.str();
}

NetPacket::NetPacket()
    : mBuffer{0, }    
    , mBufferFront(mBuffer)
    , mBufferRear(mBuffer)
    , mSize(0)
{

}

NetPacket::~NetPacket()
{
}

void NetPacket::PutData(char* data, int size)
{    
    if (mSize + size > MAX_PACKET_SIZE)
    {        
        throw PacketException(PacketException::ePacketOperationType::PutData, mSize, size);
    }

    CopyMemory(mBufferRear, data, size);
    mSize += size;
    mBufferRear += size;    
}

void NetPacket::GetData(char* outData, int size)
{
    // 단순하게 비어있냐만 체크하지말고 size보다 mSize가 작아야함
    if (size > mSize)
    {        
        throw PacketException(PacketException::ePacketOperationType::GetData, mSize, size);
    }

    CopyMemory(outData, mBufferFront, size);
    mBufferFront += size;
    mSize -= size;
}

void NetPacket::Clear()
{
    mBufferFront = mBuffer;
    mBufferRear = mBuffer;
    mSize = 0;
}

int NetPacket::GetSize()
{
    return mSize;
}

#pragma region operator>> (Put Data)
NetPacket& NetPacket::operator<<(BYTE& data)
{
    PutData((char*)&data, sizeof(BYTE));
    return *this;
}

NetPacket& NetPacket::operator<<(bool& data)
{
    PutData((char*)&data, sizeof(bool));
    return *this;
}

NetPacket& NetPacket::operator<<(char& data)
{
    PutData((char*)&data, sizeof(char));
    return *this;
}

NetPacket& NetPacket::operator<<(short& data)
{
    PutData((char*)&data, sizeof(short));
    return *this;
}

NetPacket& NetPacket::operator<<(int& data)
{
    PutData((char*)&data, sizeof(int));
    return *this;
}

NetPacket& NetPacket::operator<<(float& data)
{
    PutData((char*)&data, sizeof(float));
    return *this;
}

NetPacket& NetPacket::operator<<(double& data)
{
    PutData((char*)&data, sizeof(double));
    return *this;
}
#pragma endregion

#pragma region operator<< (Get Data)
NetPacket& NetPacket::operator>>(BYTE& outData)
{
    GetData((char*)&outData, sizeof(BYTE));
    return *this;
}

NetPacket& NetPacket::operator>>(bool& outData)
{
    GetData((char*)&outData, sizeof(bool));
    return *this;
}

NetPacket& NetPacket::operator>>(char& outData)
{
    GetData((char*)&outData, sizeof(char));
    return *this;
}

NetPacket& NetPacket::operator>>(short& outData)
{
    GetData((char*)&outData, sizeof(short));
    return *this;
}

NetPacket& NetPacket::operator>>(int& outData)
{
    GetData((char*)&outData, sizeof(int));
    return *this;
}

NetPacket& NetPacket::operator>>(float& outData)
{
    GetData((char*)&outData, sizeof(float));
    return *this;
}

NetPacket& NetPacket::operator>>(double& outData)
{
    GetData((char*)&outData, sizeof(double));
    return *this;
}
#pragma endregion

