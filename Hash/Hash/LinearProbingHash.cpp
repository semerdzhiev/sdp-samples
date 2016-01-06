/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>

#include "LinearProbingHash.h"

LinearProbingHash::LinearProbingHash(HashingFunction* pHashingFunction, size_t MaxSize) : Hash(pHashingFunction)
{
	ElementsCount = 0;
	
	BufferSize = MaxSize * 2;

	pBuffer = new int[BufferSize];

	// Mark all positions as empty
	for(size_t i = 0; i < BufferSize; i++)
	{
		pBuffer[i] = -1;
	}
}


LinearProbingHash::~LinearProbingHash()
{
	delete [] pBuffer;
}


bool LinearProbingHash::Add(const int Value)
{
	if(ElementsCount >= BufferSize)
		return false;

	int i = pHashingFunction->CalculateHash(Value);

	while(pBuffer[i] >= 0)
	{
		i = (i+1) % BufferSize;
	}

	pBuffer[i] = Value;

	ElementsCount++;

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
			i = (i+1) % BufferSize;
	}

	return false;
}

void LinearProbingHash::PrintInfo() const
{
	std::cout
		<< "LinearProbingHash:"
		<< "\n   - Used space: " << (((double)ElementsCount * 100) / BufferSize) << "%";

	PrintCommonInfo(ElementsCount, BufferSize * sizeof(int) + sizeof(*this));
}