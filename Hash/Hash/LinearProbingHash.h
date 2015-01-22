#pragma once

#include "Hash.h"

class LinearProbingHash : public Hash
{
public:
	LinearProbingHash(HashingFunction* pHashingFunction, size_t MaxSize);
	virtual ~LinearProbingHash();

	virtual bool Add(const int Value);
	virtual bool Search(const int Value);
	virtual void PrintInfo();

private:
	size_t BufferSize;
	size_t ElementsCount;
	int* pBuffer;
};