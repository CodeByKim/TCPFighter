#pragma once
#include "CommonLibrary.h"
#include "MemoryStream.h"

#define PACKET_HEADER_SIZE 3

struct PacketHeader
{
	BYTE code;
	BYTE size;
	BYTE protocol;
};

class Packet
{
public:
	Packet();
	~Packet();

	void SetMemoryStream(char* data, int size);
	PacketHeader header;
	MemoryStream* stream;
	//char* data;
};

class BasePacketData
{
public:	
	virtual void Serialize(Packet* outPacket) {}
	virtual void Deserialize(Packet* packet) {}
	virtual int GetCalcSize() = 0;
};

class PACKET_SC_CREATE_MY_CHARACTER : public BasePacketData
{
public:	
	void Deserialize(Packet* packet) override;
	int GetCalcSize() override;
	
	int id;
	char direction;
	short x;
	short y;
	char hp;
};

class PACKET_SC_CREATE_OTHER_CHARACTER : public BasePacketData
{
public:	
	void Deserialize(Packet* packet) override;
	int GetCalcSize() override;

	int id;
	char direction;
	short x;
	short y;
	char hp;
};