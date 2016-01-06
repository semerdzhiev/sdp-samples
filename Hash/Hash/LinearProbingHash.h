/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "Hash.h"


///
/// An implementation of a Linear Probing hash
///
class LinearProbingHash : public Hash
{
public:
	LinearProbingHash(HashingFunction* pHashingFunction, size_t MaxSize);
	virtual ~LinearProbingHash();

	virtual bool Add(const int Value);
	virtual bool Search(const int Value);
	virtual void PrintInfo() const;

private:
	size_t BufferSize;
	size_t ElementsCount;
	int* pBuffer;
};