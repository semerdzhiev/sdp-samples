/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <algorithm>

#include "SeparateChainingHash.h"

SeparateChainingHashStl::SeparateChainingHashStl(HashingFunction* pHashingFunction, size_t ChainsCount)
    : Hash(pHashingFunction), chainsCount(ChainsCount)
{
	pChains = new std::list<int>[chainsCount];
}

SeparateChainingHashStl::~SeparateChainingHashStl()
{
	delete [] pChains;
}

bool SeparateChainingHashStl::Add(const int Value)
{
	int hash = pHashingFunction->CalculateHash(Value);

	pChains[hash].push_back(Value);

	return true;
}

bool SeparateChainingHashStl::Search(const int Value)
{
	int hash = pHashingFunction->CalculateHash(Value);

	for(auto it = pChains[hash].cbegin(); it != pChains[hash].cend(); ++it)
	{
		if( *it == Value )
			return true;
	}

	return false;
}

void SeparateChainingHashStl::PrintInfo() const
{
	size_t maxChainSize = pChains[0].size();
	size_t sumOfSizes = pChains[0].size();
	size_t minChainSize = pChains[0].size();

	for(size_t i = 1; i < chainsCount; i++)
	{
		size_t size = pChains[i].size();

		sumOfSizes += size;
		maxChainSize = std::max(maxChainSize, size);
		minChainSize = std::min(minChainSize, size);
	}

	// NOTE: Microsoft specific. Assumes we are storing int elements
	// and  using the default allocator.
	static const size_t stlListNodeSize = sizeof(std::_List_node<int, void*>);
	
	size_t memoryUsed =
		sizeof(*this) +  // object size
		sizeof(std::list<int>) * chainsCount + // vector of lists
		sumOfSizes * stlListNodeSize; // Nodes allocated by the lists

	size_t dataSize = sumOfSizes * sizeof(int);
	size_t overhead = ((memoryUsed - dataSize) * 100) / memoryUsed;

	std::cout
		<< "SeparateChainingHashStl stats:"
		<< "\n   - Max chain size: " << maxChainSize
		<< "\n   - Avg chain size: " << (sumOfSizes / chainsCount)
		<< "\n   - Min chain size: " << minChainSize
		<< "\n   - std::list node size: " << stlListNodeSize;

	PrintCommonInfo(sumOfSizes, memoryUsed);
}



SeparateChainingHash::SeparateChainingHash(HashingFunction* pHashingFunction, size_t ChainsCount)
    : Hash(pHashingFunction), chainsCount(ChainsCount)
{
    pChains = new Box*[chainsCount];
    
    for (size_t i = 0; i < chainsCount; i++)
        pChains[i] = nullptr;
}

SeparateChainingHash::~SeparateChainingHash()
{
    Box *p = nullptr;

    for (size_t i = 0; i < chainsCount; i++)
    {
        while (pChains[i])
        {
            p = pChains[i];
            pChains[i] = pChains[i]->pNext;
            delete p;
        }
    }

    delete[] pChains;
}

bool SeparateChainingHash::Add(const int Value)
{
    int hash = pHashingFunction->CalculateHash(Value);

    try
    {
        pChains[hash] = new Box(Value, pChains[hash]);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool SeparateChainingHash::Search(const int Value)
{
    int hash = pHashingFunction->CalculateHash(Value);

    Box* p = pChains[hash];

    while (p)
    {
        if (p->data == Value)
            return true;

        p = p->pNext;
    }

    return false;
}

void SeparateChainingHash::PrintInfo() const
{
    size_t maxChainSize = GetChainSize(pChains[0]);
    size_t sumOfSizes = maxChainSize;
    size_t minChainSize = maxChainSize;

    for (size_t i = 1; i < chainsCount; i++)
    {
        size_t size = GetChainSize(pChains[i]);

        sumOfSizes += size;
        maxChainSize = std::max(maxChainSize, size);
        minChainSize = std::min(minChainSize, size);
    }

    size_t memoryUsed =
        sizeof(*this) +  // object size
        sizeof(Box*) * chainsCount + // vector of lists
        sumOfSizes * sizeof(Box); // Nodes allocated for the lists

    size_t dataSize = sumOfSizes * sizeof(int);
    size_t overhead = ((memoryUsed - dataSize) * 100) / memoryUsed;

    std::cout
        << "SeparateChainingHashStl stats:"
        << "\n   - Max chain size: " << maxChainSize
        << "\n   - Avg chain size: " << (sumOfSizes / chainsCount)
        << "\n   - Min chain size: " << minChainSize
        << "\n   - list node size: " << sizeof(Box);

    PrintCommonInfo(sumOfSizes, memoryUsed);
}

size_t SeparateChainingHash::GetChainSize(const Box * pFirst) const
{
    size_t size = 0;

    while (pFirst)
    {
        size++;
        pFirst = pFirst->pNext;
    }

    return size;
}


