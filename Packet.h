#pragma once
#include "CommonLibrary.h"

#define PACKET_HEADER_SIZE 2

struct PacketHeader
{
	unsigned short size;
};

class Packet
{
public:
	Packet()
	{

	}
	~Packet()
	{
		if (data != nullptr)
			delete[] data;
	}

	PacketHeader header;
	char* data;
};

