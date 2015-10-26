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

#include "..\LinkedList\LinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTest
{
	TEST_CLASS(LinkedListTest)
	{
	public:
		
		///
		/// Checks whether list contains all integers in [start,end].
		///
		/// The integers should be stored in ascending order in the list.
		///
		bool ContainsRange(LinkedList<int>& list, int start, int end)
		{
			Iterator<int> it = list.GetIterator();

			int i = start;

			while (!it.EndReached() && i <= end)
			{
				if (it.GetCurrent() != i)
					break;

				i++;
				it.MoveNext();
			}

			return i > end;
		}


		///
		///	Fills a list with all integers in the interval [Start, End].
		///
		void FillList(LinkedList<int>& list, int Start, int End)
		{
			for (int i = Start; i <= End; i++)
				list.AddTail(i);
		}


		///
		/// Test the behavior of an empty list
		///
		TEST_METHOD(TestEmptyList)
		{
			LinkedList<int> list;

			Assert::IsTrue(list.IsEmpty());
			Assert::AreEqual(list.GetCount(), 0);

			// The following operation should be working
			list.RemoveAll();
			list.RemoveHead();
			list.RemoveTail();

			// Changing the head and tail should fail
			Assert::IsFalse(list.SetHead(1000));
			Assert::IsFalse(list.SetTail(1000));
		}



		///
		///	Test head operations
		///
		TEST_METHOD(TestOperationsOnHead)
		{
			const int MAX_ELEM = 100;

			LinkedList<int> newList;

			// Add the numbers between 0 and 10 and make sure
			// that the list size increases accordingly and that
			// the heads can be retrieved.
			for (int i = MAX_ELEM; i >= 0; i--)
			{
				Assert::IsTrue(newList.AddHead(i));

				Assert::IsTrue(newList.GetCount() == (MAX_ELEM - i + 1));
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.GetHead() == i);
			}

			// Make sure that the elements are there
			Assert::IsTrue(ContainsRange(newList, 0, MAX_ELEM));

			// Try to change the head
			Assert::IsTrue(newList.SetHead(-100));

			Assert::IsTrue(newList.GetHead() == -100);

			Assert::IsTrue(newList.SetHead(0));

			Assert::IsTrue(newList.GetHead() == 0);

			// Now remove all heads one by one
			for (int i = 0; i <= MAX_ELEM; i++)
			{
				Assert::IsTrue(newList.GetCount() == (MAX_ELEM - i + 1));
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.GetHead() == i);

				newList.RemoveHead();
			}

			// Make sure the list is now empty
			Assert::IsTrue(newList.GetCount() == 0);
			Assert::IsTrue(newList.IsEmpty());
		}


		///
		///	Test tail operations
		///
		TEST_METHOD(TestOperationsOnTail)
		{
			const int MAX_ELEM = 5;

			LinkedList<int> newList;

			// Make sure the list is empty
			Assert::IsTrue(newList.GetCount() == 0);
			Assert::IsTrue(newList.IsEmpty());

			// Add the numbers between 0 and 10 and make sure
			// that the list sie increases accordingly and that
			// the heads can be retrieved.
			for (int i = 0; i <= MAX_ELEM; i++)
			{
				Assert::IsTrue(newList.AddTail(i));

				Assert::IsTrue(newList.GetCount() == i + 1);
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.GetTail() == i);
			}

			// Make sure that the elements are there
			Assert::IsTrue(ContainsRange(newList, 0, MAX_ELEM));

			// Try to change the head
			Assert::IsTrue(newList.SetTail(-100));

			Assert::IsTrue(newList.GetTail() == -100);

			Assert::IsTrue(newList.SetTail(MAX_ELEM));

			Assert::IsTrue(newList.GetTail() == MAX_ELEM);

			// Now remove all heads one by one
			for (int i = MAX_ELEM; i >= 0; i--)
			{
				Assert::IsTrue(newList.GetCount() == (i + 1));
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.GetTail() == i);

				newList.RemoveTail();
			}

			// Make sure the list is now empty
			Assert::IsTrue(newList.GetCount() == 0);
			Assert::IsTrue(newList.IsEmpty());
		}


		///
		///	Test at index operations
		///
		TEST_METHOD(TestIndexing)
		{
			const int MAX_ELEM = 10;

			LinkedList<int> newList;

			// Insert Before on empty list
			newList.InsertBefore(0, 3);
			newList.InsertBefore(0, 2);
			newList.InsertBefore(0, 1);

			Assert::IsTrue(ContainsRange(newList, 1, 3));

			// Insert After the head
			newList.RemoveAll();

			Assert::IsTrue(newList.IsEmpty());

			newList.AddHead(1);
			newList.InsertAfter(0, 3);
			newList.InsertAfter(0, 2);

			Assert::IsTrue(ContainsRange(newList, 1, 3));

			// Change of elements
			newList.SetAt(0, 10);
			newList.SetAt(1, 11);
			newList.SetAt(2, 12);

			Assert::IsTrue(ContainsRange(newList, 10, 12));

			// Remove elements
			newList.RemoveAt(0);
			Assert::IsTrue(ContainsRange(newList, 11, 12));

			newList.RemoveAt(1);
			Assert::IsTrue(ContainsRange(newList, 11, 11));

			newList.RemoveAt(0);
			Assert::IsTrue(newList.IsEmpty());

			// Insert Before and after
			newList.AddHead(5);
			newList.AddHead(3);
			newList.AddHead(1);

			newList.InsertAfter(2, 6);
			newList.InsertBefore(2, 4);
			newList.InsertBefore(1, 2);

			Assert::IsTrue(ContainsRange(newList, 1, 6));
		}


		
		///
		///	Test iterator functionality
		///
		TEST_METHOD(TestIterator)
		{
			const int MAX_ELEM = 1000;

			LinkedList<int> newList;

			FillList(newList, 0, MAX_ELEM);

			Iterator<int> iterator = newList.GetIterator();

			for (int i = 0; i <= MAX_ELEM; i++)
			{
				Assert::IsFalse(iterator.EndReached());
				Assert::AreEqual(iterator.GetCurrent(), i);
				iterator.MoveNext();
			}

			// Assert that the iterator is at its end
			Assert::IsTrue(iterator.EndReached());

			// Now rewind and try again
			iterator.Rewind();

			for (int i = 0; i <= MAX_ELEM; i++)
			{
				Assert::IsFalse(iterator.EndReached());
				Assert::AreEqual(iterator.GetCurrent(), i);
				iterator.MoveNext();
			}

			// Assert that the iterator is at its end
			Assert::IsTrue(iterator.EndReached());

			for (iterator.Rewind(); !iterator.EndReached(); iterator.MoveNext())
			{
				iterator.SetCurrent(iterator.GetCurrent() + 100);
			}

			Assert::IsTrue(ContainsRange(newList, 100, 100 + MAX_ELEM));
		}
	};
}