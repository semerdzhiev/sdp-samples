#include <iostream>

#include "NotReallyHash.h"

bool NotReallyHash::Add(const int Value)
{
	Data.push_back(Value);

	return true;
}

bool NotReallyHash::Search(const int Value)
{
	std::list<int>::iterator it;

	for(it = Data.begin(); it != Data.end(); it++)
	{
		if( *it == Value )
			return true;
	}

	return false;
}

void NotReallyHash::PrintInfo()
{
	size_t MemoryUsed =
		sizeof(*this) + // object size
		sizeof(std::list<int>) + // size of the list object
		Data.size() * (sizeof(int) + 16); // Elements allocated by lists
	
	std::cout << "LinkedList:"
		      << "\n   - Stored elements: " << Data.size()
			  << "\n   - Memory used: " << MemoryUsed
			  << std::endl << std::endl;
}