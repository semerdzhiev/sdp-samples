/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "UnitTestFramework.h"
#include "..\Box\Box.h"

TEST_FUNCTION(CreateEmptyBox)
{
	Box obj;
}


TEST_FUNCTION(CreateBox)
{
	Box obj(10);
}


TEST_FUNCTION(CreateBoxArray)
{
	Box* p = new Box[1000000];
	delete[] p;
}


TEST_FUNCTION(StoreAndRetrieveValue)
{
	Box obj;

	obj.Add(10.0);

	TEST(obj.Peek() == 10.0);
}


TEST_FUNCTION(StoreAndModifyValue)
{
	Box obj;

	obj.Add(10);
	obj.Add(20);

	TEST(obj.Peek() == 20);
}


TEST_FUNCTION(IsEmpty)
{
	Box obj;

	TEST(obj.IsEmpty());
}


TEST_FUNCTION(NotEmpty)
{
	Box obj;
	obj.Add(10);

	TEST(!obj.IsEmpty());
}


TEST_FUNCTION(PeekOnEmptyBox)
{
	Box obj;

	try
	{
		obj.Peek();

		// The line above should throw, so if we reach this,
		// the test has failed.
		TEST(false);
	}
	catch (std::exception &)
	{
		// OK, std::exception thrown
	}
	catch (...)
	{
		// The exception should be of type std::exception,
		// so if we reach this clause, the test has failed.
		TEST(false);
	}
}