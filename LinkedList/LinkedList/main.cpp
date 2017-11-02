/********************************************************************
*
* This file is part of the Data Structures in C++ Course Examples package.
*
* Author: Atanas Semerdzhiev
* URL: https://github.com/semerdzhiev/sdp-samples
*
*/

#include <iostream>
#include <time.h>

#include "LinkedList.h"


///
/// Fills an array with all consecutive integers between Start and End
///
void FillList(LinkedList<int> &List, int Start, int End)
{
	for (int i = Start; i <= End; i++)
		List.AddTail(i);
}


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
	std::cout << "Filling " << ElementsCount << " element(s)...\n";

	start = time(NULL);

	FillList(newList, 0, ElementsCount - 1);

	end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " sec.\n";


	//
	// TEST 2: Walk list via indexing
	//
	std::cout << "Walking the list via index...\n";

	start = time(NULL);

	int foo;

	for(int i = 0; i < ElementsCount; i++)
	{
		foo = newList.GetAt(i);
	}

	end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " sec.\n";
	

	//
	// TEST 3: Walk list via iterator
	//
	std::cout << "Walking the list via iterator...\n";

	start = time(NULL);

	// try to walk the list via iterator
	for (Iterator<int> iterator = newList.GetIterator();
         !iterator.EndReached();
	     iterator.MoveNext())
	{
		foo = iterator.GetCurrent();
	}

	end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " sec.\n";

	return 0;
}