#include "Packet.h"

Packet::Packet()
	: stream(nullptr)
{

}

Packet::~Packet()
{
	/*if (data != nullptr)
		delete[] data;*/
}

void Packet::SetMemoryStream(char* data, int size)
{
	stream = new MemoryStream(data, size);
}

void PACKET_SC_CREATE_MY_CHARACTER::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&id);
	packet->stream->ReadInt8((INT8*)&direction);
	packet->stream->ReadInt16(&x);
	packet->stream->ReadInt16(&y);
	packet->stream->ReadInt8((INT8*)&hp);
}

int PACKET_SC_CREATE_MY_CHARACTER::GetCalcSize()
{
	return 0;
}

void PACKET_SC_CREATE_OTHER_CHARACTER::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&id);
	packet->stream->ReadInt8((INT8*)&direction);
	packet->stream->ReadInt16(&x);
	packet->stream->ReadInt16(&y);
	packet->stream->ReadInt8((INT8*)&hp);
}

int PACKET_SC_CREATE_OTHER_CHARACTER::GetCalcSize()
{
	return 0;
}