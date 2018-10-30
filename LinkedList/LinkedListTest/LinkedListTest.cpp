/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
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
			LinkedList<int>::Iterator it = list.GetIterator();

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
				list.PushBack(i);
		}


		///
		/// Test the behavior of an empty list
		///
		TEST_METHOD(TestEmptyList)
		{
			LinkedList<int> list;

			Assert::IsTrue(list.IsEmpty());
			Assert::AreEqual(list.GetSize(), 0);

			// The following operation should be working
			list.Clear();
			list.PopFront();
			list.PopBack();

			// The following operatins should throw an exception
            Assert::ExpectException<std::out_of_range>(
                [&list]() { list.At(1); }
            );

            Assert::ExpectException<std::out_of_range>(
                [&list]() { list.RemoveAt(1); }
            );
		
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

                newList.PushFront(i);

				Assert::IsTrue(newList.GetSize() == (MAX_ELEM - i + 1));
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.Front() == i);
			}

			// Make sure that the elements are there
			Assert::IsTrue(ContainsRange(newList, 0, MAX_ELEM));

			// Try to change the head
			newList.Front() = -100;

			Assert::IsTrue(newList.Front() == -100);

            newList.Front() = 0;

			Assert::IsTrue(newList.Front() == 0);

			// Now remove all items, one by one, from the front
			for (int i = 0; i <= MAX_ELEM; i++)
			{
				Assert::IsTrue(newList.GetSize() == (MAX_ELEM - i + 1));
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.Front() == i);

				newList.PopFront();
			}

			// Make sure the list is now empty
			Assert::IsTrue(newList.GetSize() == 0);
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
			Assert::IsTrue(newList.GetSize() == 0);
			Assert::IsTrue(newList.IsEmpty());

			// Add the numbers between 0 and 10 and make sure
			// that the list sie increases accordingly and that
			// the heads can be retrieved.
			for (int i = 0; i <= MAX_ELEM; i++)
			{
				newList.PushBack(i);

				Assert::IsTrue(newList.GetSize() == i + 1);
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.Back() == i);
			}

			// Make sure that the elements are there
			Assert::IsTrue(ContainsRange(newList, 0, MAX_ELEM));

			// Try to change the tail
			newList.Back() = -100;

			Assert::IsTrue(newList.Back() == -100);

            newList.Back() = MAX_ELEM;

			Assert::IsTrue(newList.Back() == MAX_ELEM);

            // Now remove all items, one by one, from the back
			for (int i = MAX_ELEM; i >= 0; i--)
			{
				Assert::IsTrue(newList.GetSize() == (i + 1));
				Assert::IsFalse(newList.IsEmpty());

				Assert::IsTrue(newList.Back() == i);

				newList.PopBack();
			}

			// Make sure the list is now empty
			Assert::IsTrue(newList.GetSize() == 0);
			Assert::IsTrue(newList.IsEmpty());
		}

        ///
        ///	Test the clear operation
        ///
        TEST_METHOD(TestClear)
        {
            LinkedList<int> newList;

            FillList(newList, 1, 10);

            Assert::IsTrue(ContainsRange(newList, 1, 10));

            newList.Clear();

            Assert::IsTrue(newList.IsEmpty());
        }


		///
		///	Test at index operations
		///
		TEST_METHOD(TestIndexing)
		{
			const int MAX_ELEM = 10;

			LinkedList<int> newList;

            FillList(newList, 1, 3);

			Assert::IsTrue(ContainsRange(newList, 1, 3));

			// Change of elements
			newList.At(0) = 10;
			newList.At(1) = 11;
			newList.At(2) = 12;

			Assert::IsTrue(ContainsRange(newList, 10, 12));

			// Remove elements
			newList.RemoveAt(0);
			Assert::IsTrue(ContainsRange(newList, 11, 12));

			newList.RemoveAt(1);
			Assert::IsTrue(ContainsRange(newList, 11, 11));

			newList.RemoveAt(0);
			Assert::IsTrue(newList.IsEmpty());
		}


		
		///
		///	Test iterator functionality
		///
		TEST_METHOD(TestIterator)
		{
			const int MAX_ELEM = 1000;

			LinkedList<int> newList;

			FillList(newList, 0, MAX_ELEM);

			LinkedList<int>::Iterator it = newList.GetIterator();

			for (int i = 0; i <= MAX_ELEM; i++)
			{
				Assert::IsFalse(it.EndReached());
				Assert::AreEqual(it.GetCurrent(), i);
				it.MoveNext();
			}

			// Assert that the iterator is at its end
			Assert::IsTrue(it.EndReached());

			// Now rewind and try again
			it.Rewind();

			for (int i = 0; i <= MAX_ELEM; i++)
			{
				Assert::IsFalse(it.EndReached());
				Assert::AreEqual(it.GetCurrent(), i);
				it.MoveNext();
			}

			// Assert that the iterator is at its end
			Assert::IsTrue(it.EndReached());

			for (it.Rewind(); !it.EndReached(); it.MoveNext())
			{
				it.SetCurrent(it.GetCurrent() + 100);
			}

			Assert::IsTrue(ContainsRange(newList, 100, 100 + MAX_ELEM));
		}
	};
}