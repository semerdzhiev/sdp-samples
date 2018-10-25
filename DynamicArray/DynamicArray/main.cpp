/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>

#include "DynamicArray.h"

int main()
{
	DynamicArray da;

	//
	// 1: Add new elements to the array
	//
	std::cout << "Adding numbers to the array: ";

	for(int i = 0; i < 10; i++)
	{
		
		da.PushBack(i);
		std::cout << i << ", ";
	}

	std::cout << "done\n\n";


	//
	// 2: Print the elements using operator[]
	//
	std::cout << "The array contains: " << da[0];

	for(size_t i = 1; i < da.GetSize(); i++)
	{
		std::cout << ", " << da[i];
	}

	std::cout << "\n\n";
	

	//
	// 3: Modify the elements using operator[]
	//
	std::cout << "Multiplying each array element by 10...\n";

	for(size_t i = 0; i < da.GetSize(); i++)
	{
		// Note that we cannot use the *= operator,
        // as it is not defined for DynamicArrayElementProxy
		da[i] = da[i] * 10;
	}

	da.Print();
	std::cout << "\n";


	//
	// 4: Constant array
	//
	std::cout << "Let's go constant!\n";

	const DynamicArray & cda = da;

	std::cout << "The fifth element is " << cda[5] << "\n\n"; // This is ok...

	// ...but the code below will not compile:
	// cda[5] = 10;


	//
	// 5: Try to access an element at an invalid index
	//
	std::cout << "Trying to access an invalid index...\n";

	try
	{
		da.GetAt(da.GetSize() + 1);
	}
	catch(std::out_of_range& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}


	//
	// 6: Access the elements of the array using an interator
	//

	std::cout << "\nAccess the elements of the array using an interator...\n";

	for (DynamicArray::Iterator it = da.GetIterator();
		!it.EndReached();
		it.MoveNext())
	{
		std::cout << it.GetCurrent() << " ";
	}

	std::cout << "\n\n";

	return 0;
}

