/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\LinkedList\Box.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTest
{		
	TEST_CLASS(BoxTest)
	{
	public:
		void TestSingleBox(Box<int>& box)
		{
			Assert::IsTrue(box.Data == 100, L"Data is not stored properly");
			Assert::IsNull(box.pNext, L"pNext is not NULL on a single box");
			Assert::IsFalse(box.HasSuccessor(), L"A single box should have no successors");
		}

		TEST_METHOD(TestSingleBox)
		{
			Box<int> box(100);

			TestSingleBox(box);
		}

		TEST_METHOD(TestChain)
		{
			Box<int> boxEnd(100);
			Box<int> boxStart(200, &boxEnd);

			// Test whether adding a single box to a chain changes it
			TestSingleBox(boxEnd);

			Assert::IsTrue(boxStart.Data == 200);
			Assert::IsTrue(boxStart.pNext == &boxEnd);
			Assert::IsTrue(boxStart.HasSuccessor());
		}
	};
}