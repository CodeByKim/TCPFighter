#pragma once
#include "CommonLibrary.h"

#define PACKET_HEADER_SIZE 3

struct PacketHeader
{
	BYTE code;
	BYTE size;
	BYTE protocol;
};

class PacketException : public std::exception
{
public:
	enum class ePacketOperationType
	{
		GetData,
		PutData
	};

public:
	PacketException(ePacketOperationType type, int packetSize, int trySize);	
	~PacketException();

	char const* what() const override;
	std::string Log();

private:
	ePacketOperationType mType;
	int mPacketSize;
	int mTrySize;	
};

class NetPacket
{
public:
	NetPacket();
	~NetPacket();

	void PutData(char* data, int size);
	void GetData(char* outData, int size);
	void Clear();
	int GetSize();
	void SetHeader(PacketHeader header)
	{
		this->header = header;
	}

	void SetHeader(int protocol)
	{
		header.code = 0x89;
		header.size = mSize;
		header.protocol = protocol;
	}

	void SetPayload(char* buffer, int size)
	{
		CopyMemory(mBuffer, buffer, size);
		mSize = size;
	}

	char* GetBuffer()
	{
		return mBuffer;
	}

	NetPacket& operator<< (BYTE& data);
	NetPacket& operator<< (bool& data);
	NetPacket& operator<< (char& data);
	NetPacket& operator<< (short& data);
	NetPacket& operator<< (int& data);
	NetPacket& operator<< (float& data);
	NetPacket& operator<< (double &data);

	NetPacket& operator>> (BYTE& outData);
	NetPacket& operator>> (bool& outData);
	NetPacket& operator>> (char& outData);
	NetPacket& operator>> (short& outData);
	NetPacket& operator>> (int& outData);
	NetPacket& operator>> (float& outData);
	NetPacket& operator>> (double& outData);

	PacketHeader header;

private:
	static int constexpr MAX_PACKET_SIZE = 1024; 	
	
	char mBuffer[MAX_PACKET_SIZE];
	char* mBufferFront;
	char* mBufferRear;
	int mSize;
};