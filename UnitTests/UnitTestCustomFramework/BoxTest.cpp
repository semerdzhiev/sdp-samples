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

TEST_CASE("Box", CreateEmptyBox)
{
	Box obj;
}


TEST_CASE("Box", CreateBox)
{
	Box obj(10);
}


TEST_CASE("Box", CreateBoxArray)
{
	Box* p = new Box[1000000];
	delete[] p;
}


TEST_CASE("Box", StoreAndRetrieveValue)
{
	Box obj;

	obj.Add(10.0);

	Assert::AreEqual(obj.Peek(), 10.0);
}


TEST_CASE("Box", StoreAndModifyValue)
{
	Box obj;

	obj.Add(10);
	obj.Add(20);

	Assert::AreEqual(obj.Peek(), 20);
}


TEST_CASE("Box", IsEmpty)
{
	Box obj;

	Assert::IsTrue(obj.IsEmpty());
}


TEST_CASE("Box", NotEmpty)
{
	Box obj;
	obj.Add(10);

	Assert::IsFalse(obj.IsEmpty());
}


TEST_CASE("Box", PeekOnEmptyBox)
{
	Box obj;

	try
	{
		obj.Peek();

		// The line above should throw, so if we reach this,
		// the test has failed.
		Assert::Fail();
	}
	catch (std::exception &)
	{
		// OK, std::exception thrown
	}
	catch (...)
	{
		// The exception should be of type std::exception,
		// so if we reach this clause, the test has failed.
		Assert::Fail();
	}
}