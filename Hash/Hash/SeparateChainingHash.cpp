#include <iostream>
#include <algorithm>

#include "SeparateChainingHash.h"

SeparateChainingHash::SeparateChainingHash(HashingFunction* pHashingFunction, size_t ChainsCount) : Hash(pHashingFunction)
{
	pChains = new std::list<int>[ChainsCount];

	this->ChainsCount = ChainsCount;
}

SeparateChainingHash::~SeparateChainingHash()
{
	delete [] pChains;
}

bool SeparateChainingHash::Add(const int Value)
{
	int hash = pHashingFunction->CalculateHash(Value);

	pChains[hash].push_back(Value);

	return true;
}

bool SeparateChainingHash::Search(const int Value)
{
	int hash = pHashingFunction->CalculateHash(Value);

	std::list<int>::iterator it;

	for(it = pChains[hash].begin(); it != pChains[hash].end(); it++)
	{
		if( *it == Value )
		{
			return true;
		}
	}

	return false;
}

void SeparateChainingHash::PrintInfo()
{
	size_t maxChainSize = pChains[0].size();
	size_t sumOfSizes = pChains[0].size();
	size_t minChainSize = pChains[0].size();

	for(size_t i = 1; i < ChainsCount; i++)
	{
		size_t size = pChains[i].size();

		sumOfSizes += size;
		maxChainSize = std::max(maxChainSize, size);
		minChainSize = std::min(minChainSize, size);
	}

	size_t MemoryUsed =
		sizeof(*this) +  // object size
		sizeof(std::list<int>) * ChainsCount + // vector of lists
		sumOfSizes * (sizeof(int) + 16); // Elements allocated by lists

	std::cout << "SeparateChainingHash stats:"
			  << "\n   - Max chain size: " << maxChainSize
			  << "\n   - Avg chain size: " << (sumOfSizes / ChainsCount)
			  << "\n   - Min chain size: " << minChainSize
			  << "\n   - Memory used: " << MemoryUsed << " byte(s)"
			  << std::endl << std::endl;
}