#include "Packet.h"
#include "MemoryStream.h"

Packet::Packet()
	: stream(nullptr)
{

}

Packet::~Packet()
{
	if (stream != nullptr)
		delete stream;
}

void Packet::SetMemoryStream(MemoryStream* stream)
{
	this->stream = stream;
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

void PACKET_SC_CREATE_OTHER_CHARACTER::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&id);
	packet->stream->ReadInt8((INT8*)&direction);
	packet->stream->ReadInt16(&x);
	packet->stream->ReadInt16(&y);
	packet->stream->ReadInt8((INT8*)&hp);
}

void PACKET_CS_MOVE_START::Serialize(MemoryStream* outStream)
{
	outStream->WriteInt8(direction);
	outStream->WriteInt16(x);
	outStream->WriteInt16(y);
}

void PACKET_CS_MOVE_STOP::Serialize(MemoryStream* outStream)
{
	outStream->WriteInt8(direction);
	outStream->WriteInt16(x);
	outStream->WriteInt16(y);
}

void PACKET_SC_MOVE_START::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&id);
	packet->stream->ReadInt8((INT8*)&direction);
	packet->stream->ReadInt16(&x);
	packet->stream->ReadInt16(&y);	
}

void PACKET_SC_MOVE_STOP::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&id);
	packet->stream->ReadInt8((INT8*)&direction);
	packet->stream->ReadInt16(&x);
	packet->stream->ReadInt16(&y);	
}

void PACKET_CS_ATTACK1::Serialize(MemoryStream* outStream)
{
	outStream->WriteInt8(direction);
	outStream->WriteInt16(x);
	outStream->WriteInt16(y);
}

void PACKET_SC_ATTACK1::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&id);
	packet->stream->ReadInt8((INT8*)&direction);
	packet->stream->ReadInt16(&x);
	packet->stream->ReadInt16(&y);
}

void PACKET_SC_DAMAGE::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&attackID);
	packet->stream->ReadInt32(&hitID);
	packet->stream->ReadInt8((INT8*)&damage);
}