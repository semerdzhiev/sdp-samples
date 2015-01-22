#pragma once

#include <list>

#include "Hash.h"

class SeparateChainingHash : public Hash
{
public:
	SeparateChainingHash(HashingFunction* pHashingFunction, size_t ChainsCount);
	virtual ~SeparateChainingHash();

	virtual bool Add(const int Value);
	virtual bool Search(const int Value);
	virtual void PrintInfo();

private:
	size_t ChainsCount;
	std::list<int> * pChains;
};
