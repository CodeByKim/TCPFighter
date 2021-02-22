#pragma once
#include "CommonLibrary.h"

class MemoryStream
{
public:
	MemoryStream(char* buffer, int length);
	~MemoryStream();

	void WriteInt8(INT8 data);
	void WriteInt16(INT16 data);
	void WriteInt32(INT32 data);
	void WriteInt64(INT64 data);

	void ReadInt8(INT8* outData);
	void ReadInt16(INT16* outData);
	void ReadInt32(INT32* outData);
	void ReadInt64(INT64* outData);

	int GetOffset();
	char* GetBuffer();

private:
	int mOffset;
	char* mBuffer;
};

