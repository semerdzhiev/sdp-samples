/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <list>

#include "Hash.h"


///
/// An implementation of a separate chaining hash, using the STL list class
///
class SeparateChainingHashStl : public Hash
{
private:
	size_t chainsCount;
	std::list<int> * pChains;

public:
	SeparateChainingHashStl(HashingFunction* pHashingFunction, size_t ChainsCount);
	virtual ~SeparateChainingHashStl();

	bool Add(const int Value) override;
	bool Search(const int Value) override;
	void PrintInfo() const override;
};


///
/// An implementation of a separate chaining hash
///
class SeparateChainingHash : public Hash
{
    struct Box {
        int data;
        Box* pNext;

        Box(int data, Box* pNext = nullptr)
            : data(data), pNext(pNext)
        {
            // Nothing to do here
        }
    };

private:
    size_t chainsCount;
    Box ** pChains;

public:
    SeparateChainingHash(HashingFunction* pHashingFunction, size_t ChainsCount);
    ~SeparateChainingHash() override;

    bool Add(const int Value) override;
    bool Search(const int Value) override;
    void PrintInfo() const override;

    size_t GetChainSize(const Box* pFirst) const;
};
