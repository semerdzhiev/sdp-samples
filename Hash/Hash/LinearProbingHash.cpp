/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>

#include "LinearProbingHash.h"

LinearProbingHash::LinearProbingHash(HashingFunction* pHashingFunction, size_t MaxSize)
    : Hash(pHashingFunction), elementsCount(0), bufferSize(MaxSize*2)
{
	pBuffer = new int[bufferSize];

	// Mark all positions as empty
	for(size_t i = 0; i < bufferSize; i++)
		pBuffer[i] = -1;
}


LinearProbingHash::~LinearProbingHash()
{
	delete [] pBuffer;
}


bool LinearProbingHash::Add(const int Value)
{
	if(elementsCount >= bufferSize)
		return false;

	int i = pHashingFunction->CalculateHash(Value);

	while(pBuffer[i] >= 0)
		i = (i+1) % bufferSize;

	pBuffer[i] = Value;

	elementsCount++;

	return true;
}

bool LinearProbingHash::Search(const int Value)
{
	int i = pHashingFunction->CalculateHash(Value);

	while(pBuffer[i] >= 0)
	{
		if(pBuffer[i] == Value)
			return true;
		else
			i = (i+1) % bufferSize;
	}

	return false;
}

void LinearProbingHash::PrintInfo() const
{
	std::cout
		<< "LinearProbingHash:"
		<< "\n   - Used space: " << (((double)elementsCount * 100) / bufferSize) << "%";

	PrintCommonInfo(elementsCount, bufferSize * sizeof(int) + sizeof(*this));
}