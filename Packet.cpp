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

//int PACKET_SC_CREATE_MY_CHARACTER::GetCalcSize()
//{
//	return 0;
//}

void PACKET_SC_CREATE_OTHER_CHARACTER::Deserialize(Packet* packet)
{
	packet->stream->ReadInt32(&id);
	packet->stream->ReadInt8((INT8*)&direction);
	packet->stream->ReadInt16(&x);
	packet->stream->ReadInt16(&y);
	packet->stream->ReadInt8((INT8*)&hp);
}

//int PACKET_SC_CREATE_OTHER_CHARACTER::GetCalcSize()
//{
//	return 0;
//}

void PACKET_CS_MOVE_START::Serialize(MemoryStream* outStream)
{
	outStream->WriteInt8(direction);
	outStream->WriteInt16(x);
	outStream->WriteInt16(y);

	/*outPacket->stream = new MemoryStream();
	outPacket->stream->WriteInt8(direction);
	outPacket->stream->WriteInt16(x);
	outPacket->stream->WriteInt16(y);*/
}

//int PACKET_CS_MOVE_START::GetCalcSize()
//{
//	return 0;
//}

void PACKET_CS_MOVE_STOP::Serialize(MemoryStream* outStream)
{
	outStream->WriteInt8(direction);
	outStream->WriteInt16(x);
	outStream->WriteInt16(y);
}

//int PACKET_CS_MOVE_STOP::GetCalcSize()
//{
//	return 0;
//}