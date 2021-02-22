#include "RingBuffer.h"

RingBuffer::RingBuffer(int size)
	: mBuffer(nullptr)
	, mBufferFront(nullptr)
	, mBufferRear(nullptr)
	, mBufferEnd(nullptr)
	, mCapacity(size)
	, mSize(0)
{
	mBuffer = new char[mCapacity];
	mBufferFront = mBuffer;
	mBufferRear = mBuffer;
	mBufferEnd = mBuffer + mCapacity - 1;
}

RingBuffer::~RingBuffer()
{

}

bool RingBuffer::Enqueue(char* data, int size)
{
	if (size > GetRemainQueueSize())
	{
		return false;
	}

	// �������� ����� ������ ���� �������� ���� ��
	// �̶��� �����Ͱ� �ѹ��� ����.
	if (size <= (mBufferEnd - mBufferRear - 1))
	{
		CopyMemory(mBufferRear, data, size);
		mBufferRear += size;
	}
	else
	{
		int tempSize = mBufferEnd - mBufferRear;
		CopyMemory(mBufferRear, data, tempSize);
		mBufferRear = mBuffer;

		CopyMemory(mBufferRear, data + tempSize, size - tempSize);
		mBufferRear += (size - tempSize);
	}

	mSize += size;
	return true;
}

bool RingBuffer::Dequeue(char* outData, int size)
{
	if (size > mSize)
	{
		return false;
	}

	//�����͸� �ѹ��� ������ �� �ִ°��
	//�ϴ� End�տ� �����Ͱ� �� ������ �ȴ�. �׷� �ѹ��� ������ �� ����
	if (size <= (mBufferEnd - mBufferFront - 1))
	{
		CopyMemory(outData, mBufferFront, size);
		mBufferFront += size;
	}
	else
	{
		//������ �����Ͱ� �ָ��ϰ� end�� front�� ��ģ���
		//�켱 end���� �а�
		int tempSize = mBufferEnd - mBufferFront;
		CopyMemory(outData, mBufferFront, tempSize);
		mBufferFront = mBuffer;

		CopyMemory(outData + tempSize, mBufferFront, size - tempSize);
		mBufferFront += (size - tempSize);
	}

	mSize -= size;
	return true;
}

bool RingBuffer::Peek(char* outData, int size)
{
	if (size > mSize)
	{
		return false;
	}

	//�����͸� �ѹ��� ������ �� �ִ°��
	//�ϴ� End�տ� �����Ͱ� �� ������ �ȴ�. �׷� �ѹ��� ������ �� ����
	if (size <= (mBufferEnd - mBufferFront - 1))
	{
		CopyMemory(outData, mBufferFront, size);
	}
	else
	{
		//������ �����Ͱ� �ָ��ϰ� end�� front�� ��ģ���
		//�켱 end���� �а�
		int tempSize = mBufferEnd - mBufferFront;
		CopyMemory(outData, mBufferFront, tempSize);
		CopyMemory(outData + tempSize, mBuffer, size - tempSize);
	}

	return true;
}

void RingBuffer::MoveFront(int size)
{
	if (size <= (mBufferEnd - mBufferFront - 1))
	{
		mBufferFront += size;
	}
	else
	{
		int tempSize = mBufferEnd - mBufferFront;

		mBufferFront = mBuffer;
		mBufferFront += (size - tempSize);
	}

	mSize -= size;
}

bool RingBuffer::IsEmpty()
{
	return mBufferFront == mBufferRear;
}

int RingBuffer::GetRemainQueueSize()
{
	return mCapacity - 1 - mSize;
}