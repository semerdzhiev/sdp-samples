/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <list>

#include "Hash.h"

class SeparateChainingHashStl : public Hash
{
public:
	SeparateChainingHashStl(HashingFunction* pHashingFunction, size_t ChainsCount);
	virtual ~SeparateChainingHashStl();

	virtual bool Add(const int Value);
	virtual bool Search(const int Value);
	virtual void PrintInfo() const;

private:
	size_t ChainsCount;
	std::list<int> * pChains;
};

class SeparateChainingHash : public Hash
{
    class Box {
    public:
        Box(int Data, Box* pNext = NULL)
        {
            this->Data = Data;
            this->pNext = pNext;
        }

        int Data;
        Box* pNext;
    };
public:
    SeparateChainingHash(HashingFunction* pHashingFunction, size_t ChainsCount);
    virtual ~SeparateChainingHash();

    virtual bool Add(const int Value);
    virtual bool Search(const int Value);
    virtual void PrintInfo() const;

    size_t GetChainSize(const Box* pFirst) const;

private:
    size_t ChainsCount;
    Box ** pChains;
};
