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

void NotReallyHash::PrintInfo() const
{
	// NOTE: Microsoft specific. Assumes we are storing int elements
	// and  using the default allocator.
	static const size_t stlListNodeSize = sizeof(std::_List_node<int, void*>);

	size_t memoryUsed =
		sizeof(*this) +  // object size
		Data.size() * stlListNodeSize; // nodes allocated by the list
	
	std::cout << "NotReallyHash:";

	PrintCommonInfo(Data.size(), memoryUsed);
}