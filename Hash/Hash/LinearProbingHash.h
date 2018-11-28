/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "Hash.h"

///
/// An implementation of a linear probing hash
///
class LinearProbingHash : public Hash
{
    size_t bufferSize;
	size_t elementsCount;
	int* pBuffer;

public:
    LinearProbingHash(HashingFunction* pHashingFunction, size_t MaxSize);
	virtual ~LinearProbingHash();

	bool Add(const int Value) override;
	bool Search(const int Value) override;
	void PrintInfo() const override;
};