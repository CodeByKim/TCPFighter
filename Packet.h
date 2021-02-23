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

	void SetMemoryStream(MemoryStream* stream);
	void SetMemoryStream(char* data, int size);
	void SetHeader(BYTE protocol)
	{
		header.code = 0x89;
		header.size = stream->GetOffset();
		header.protocol = protocol;
	}
	PacketHeader header;
	MemoryStream* stream;
	//char* data;
};

class BasePacketData
{
public:	
	virtual void Serialize(MemoryStream* outStream) {}
	virtual void Deserialize(Packet* packet) {}
	//virtual int GetCalcSize() = 0;
};

class PACKET_SC_CREATE_MY_CHARACTER : public BasePacketData
{
public:	
	void Deserialize(Packet* packet) override;
	//int GetCalcSize() override;
	
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
	//int GetCalcSize() override;

	int id;
	char direction;
	short x;
	short y;
	char hp;
};

class PACKET_SC_DELETE_CHARACTER : public BasePacketData
{
public:
	void Deserialize(Packet* packet) override;

	int id;
};

class PACKET_SC_MOVE_START : public BasePacketData
{
public:
	void Deserialize(Packet* packet) override;

	int id;
	char direction;
	short x;
	short y;
};

class PACKET_SC_MOVE_STOP : public BasePacketData
{
public:
	void Deserialize(Packet* packet) override;

	int id;
	char direction;
	short x;
	short y;
};

class PACKET_CS_MOVE_START : public BasePacketData
{
public:
	void Serialize(MemoryStream* outStream) override;
	//int GetCalcSize() override;
	char direction;
	short x;
	short y;
};

class PACKET_CS_MOVE_STOP : public BasePacketData
{
public:
	void Serialize(MemoryStream* outStream) override;
	//int GetCalcSize() override;
	char direction;
	short x;
	short y;
};
