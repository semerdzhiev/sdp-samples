/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <ctime>

#include "LinkedList.h"

///
/// Fills an array with all consecutive integers between Start and End
///
void FillList(LinkedList<int> &List, int Start, int End)
{
	for (int i = Start; i <= End; i++)
		List.PushBack(i);
}

template class LinkedList<int>;

int main()
{
	// Decide how many element to use for the tests
	int ElementsCount = 0;
	std::cout << "\nHow many elements to test with?\n: ";
	std::cin >> ElementsCount;
	
	// Create a linked list to test with
	LinkedList<int> newList;

	// These will be used to measure execution time
	time_t start, end;

    //
	// TEST 1: Fill the list with elements
	//
	std::cout << "\nFilling " << ElementsCount << " element(s)...\n";
	start = std::time(nullptr);

	FillList(newList, 0, ElementsCount - 1);

	end = std::time(nullptr);
	std::cout << "   Execution took " << (end - start) << " sec.\n";


	//
	// TEST 2: Iterate the list via the indexing operation
	//
	std::cout << "\nIterating the list with the indexing operation...\n";
	start = std::time(nullptr);

	int foo;

	for(int i = 0; i < ElementsCount; i++)
		foo = newList.At(i);

	end = std::time(nullptr);
	std::cout << "   Execution took " << (end - start) << " sec.\n";
	

	//
	// TEST 3: Iterate the list with an iterator
	//
	std::cout << "\nIterating the list with an iterator...\n";
	start = std::time(nullptr);

	// try to walk the list via iterator
	for (LinkedList<int>::Iterator it = newList.GetIterator();
         !it.EndReached();
	     it.MoveNext())
	{
		foo = it.GetCurrent();
	}

	end = std::time(nullptr);
	std::cout << "   Execution took " << (end - start) << " sec.\n";

	return 0;
}