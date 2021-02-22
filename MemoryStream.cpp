#include "MemoryStream.h"

MemoryStream::MemoryStream(char* buffer, int length)
{
	mBuffer = new char[length];
	CopyMemory(mBuffer, buffer, length);

	mOffset = 0;
}

MemoryStream::~MemoryStream()
{
	if (mBuffer != nullptr)
		delete[] mBuffer;
}

void MemoryStream::WriteInt8(INT8 data)
{
	CopyMemory(mBuffer + mOffset, &data, sizeof(INT8));
	mOffset += sizeof(INT8);
}

void MemoryStream::WriteInt16(INT16 data)
{
	CopyMemory(mBuffer + mOffset, &data, sizeof(INT16));
	mOffset += sizeof(INT16);
}

void MemoryStream::WriteInt32(INT32 data)
{
	CopyMemory(mBuffer + mOffset, &data, sizeof(INT32));
	mOffset += sizeof(INT32);
}

void MemoryStream::WriteInt64(INT64 data)
{
	CopyMemory(mBuffer + mOffset, &data, sizeof(INT64));
	mOffset += sizeof(INT64);
}

void MemoryStream::ReadInt8(INT8* outData)
{
	CopyMemory(outData, mBuffer + mOffset, sizeof(INT8));
	mOffset += sizeof(INT8);
}

void MemoryStream::ReadInt16(INT16* outData)
{
	CopyMemory(outData, mBuffer + mOffset, sizeof(INT16));
	mOffset += sizeof(INT16);
}

void MemoryStream::ReadInt32(INT32* outData)
{
	CopyMemory(outData, mBuffer + mOffset, sizeof(INT32));
	mOffset += sizeof(INT32);
}

void MemoryStream::ReadInt64(INT64* outData)
{
	CopyMemory(outData, mBuffer + mOffset, sizeof(INT64));
	mOffset += sizeof(INT64);
}

int MemoryStream::GetOffset()
{
	return mOffset;
}

char* MemoryStream::GetBuffer()
{
	return mBuffer;
}