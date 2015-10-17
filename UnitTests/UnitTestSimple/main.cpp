/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */
 
#include <iostream>
#include "../Box/Box.h"

void Test_CreateEmptyBox()
{
	std::cout << "Create empty box...";
	
	Box obj;
	
	std::cout << "OK\n";
}


void Test_CreateBox()
{
	std::cout << "Create box...";
	
	Box obj(10);
	
	std::cout << "OK\n";
}


void Test_CreateBoxArray()
{
	std::cout << "Create and delete box array...";

	Box* p = new Box[1000000];
	delete[] p;

	std::cout << "OK\n";
}


void Test_StoreAndRetrieveValue()
{
	std::cout << "Store and retrieve value...";

	Box obj;

	obj.Add(10);

	std::cout << (obj.Peek() == 10 ? "OK\n" : "Failed\n");
}


void Test_StoreAndModifyValue()
{
	std::cout << "Store and modify value...";

	Box obj;

	obj.Add(10);
	obj.Add(20);

	std::cout << (obj.Peek() == 20 ? "OK\n" : "Failed\n");
}


void Test_IsEmpty()
{
	std::cout << "Empty state...";

	Box obj;

	std::cout << (obj.IsEmpty() ? "OK\n" : "Failed\n");
}


void Test_NotEmpty()
{
	std::cout << "Non-empty state...";

	Box obj;
	obj.Add(10);

	std::cout << (!obj.IsEmpty() ? "OK\n" : "Failed\n");
}


void Test_PeekOnEmptyBox()
{
	std::cout << "Peek on empty box...";

	Box obj;

	try
	{
		obj.Peek();
		
		// The line above should throw, so if we reach this,
		// the test has failed.
		std::cout << "Failed (does not throw)\n";
	}
	catch(std::exception &)
	{
		// OK, std::exception thrown
		std::cout << "OK\n";
	}
	catch (...)
	{
		// The exception should be of type std::exception,
		// so if we reach this clause, the test has failed.
		std::cout << "Failed (wrong exception type)\n";
	}
}

int main()
{
	std::cout << "Testing class Box:\n";

	Test_CreateEmptyBox();
	Test_CreateBox();
	Test_CreateBoxArray();
	Test_StoreAndRetrieveValue();
	Test_StoreAndModifyValue();
	Test_IsEmpty();
	Test_NotEmpty();
	Test_PeekOnEmptyBox();

	return 0;
}