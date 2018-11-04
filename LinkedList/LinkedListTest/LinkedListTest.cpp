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
    //
    // Implicitly, the class checks that the default constructed list is empty
    // (IsEmpty_ReturnsTrue + GetSize_ReturnsZero on the EmptyList object)
    //
    TEST_CLASS(EmptyListTest)
    {
        LinkedList<int> EmptyList;

        TEST_METHOD(IsEmpty_ReturnsTrue)
        {
            Assert::IsTrue(EmptyList.IsEmpty());
        }

        TEST_METHOD(GetSize_ReturnsZero)
        {
            Assert::AreEqual(EmptyList.GetSize(), size_t(0));
        }

        TEST_METHOD(Clear_ShouldNotThrow)
        {
            EmptyList.Clear();
        }

        TEST_METHOD(PopFront_ShouldNotThrow)
        {
            EmptyList.PopFront();
        }

        TEST_METHOD(PopBack_ShouldNotThrow)
        {
            EmptyList.PopBack();
        }

        TEST_METHOD(At_Throws)
        {
            Assert::ExpectException<std::out_of_range>(
                [this]() { EmptyList.At(1); } // Attempt to retrieve the element at a given position
            );
        }

        TEST_METHOD(RemoveAt_Throws)
        {
            Assert::ExpectException<std::out_of_range>(
                [this]() { EmptyList.RemoveAt(1); } // Attempt to remove at a given position
            );
        }

        TEST_METHOD(Front_Throws)
        {
            Assert::ExpectException<std::exception>(
                [this]() { EmptyList.Front(); } // Retrieve the front element
            );
        }

        TEST_METHOD(Back_Throws)
        {
            Assert::ExpectException<std::exception>(
                [this]() { EmptyList.Back(); } // Retrieve the rearmost element
            );
        }
    };

	TEST_CLASS(ListTest)
	{
    private:
        LinkedList<int> EmptyList;
        LinkedList<int> SampleList;
        const int SampleRangeStart;
        const int SampleRangeEnd;
        const size_t SampleSize;

    public:
        ListTest()
            : SampleRangeStart(1),
              SampleRangeEnd(10),
              SampleSize(SampleRangeEnd - SampleRangeStart + 1)
        {
            Logger::WriteMessage(L"ListTest::ListTest()");
            Fill(SampleList, SampleRangeStart, SampleRangeEnd);
        }

        ~ListTest()
        {
            Logger::WriteMessage(L"ListTest::~ListTest()");
        }

        TEST_METHOD_INITIALIZE(TestMethodInitialize)
        {
            Logger::WriteMessage(L"TestMethodInitialize()");
        }

        TEST_METHOD_CLEANUP(TestMethodCleanup)
        {
            Logger::WriteMessage(L"TestMethodCleanup()");
        }

        TEST_CLASS_INITIALIZE(TestClassInitialize)
        {
            Logger::WriteMessage(L"TestClassInitialize");
        }

        TEST_CLASS_CLEANUP(TestClassCleanup)
        {
            Logger::WriteMessage(L"TestClassCleanup");
        }
		
		///
		/// Checks whether list contains all integers in [start,end].
		///
		/// The integers should be stored in ascending order in the list.
		///
		bool ContainsRange(const LinkedList<int>& list, int start, int end)
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
		void Fill(LinkedList<int>& list, int Start, int End)
		{
			for (int i = Start; i <= End; i++)
				list.PushBack(i);
		}


        ///
        /// Asserts that the list is empty
        ///
        void AssertEmpty(const LinkedList<int>& list)
        {
            Assert::IsTrue(list.IsEmpty());
            Assert::AreEqual(list.GetSize(), size_t(0));
        }

        void AssertContainsRange(const LinkedList<int>& list, int start, int end)
        {
            Assert::IsTrue(ContainsRange(list, start, end));
        }

        void AssertContainsSampleRange(const LinkedList<int>& list)
        {
            Assert::IsTrue(ContainsRange(list, SampleRangeStart, SampleRangeEnd));
        }

        void AssertSize(const LinkedList<int>& list, size_t size)
        {
            Assert::AreEqual(list.GetSize(), size);
        }



        TEST_METHOD(SelfCheck)
        {
            Assert::IsTrue(ContainsRange(SampleList, 1, 10));
        }

        TEST_METHOD(Clear_EmptiesTheList)
        {
            SampleList.Clear();
            AssertEmpty(SampleList);
        }

        TEST_METHOD(CopyConstructor_CopiesCorrectly)
        {
            LinkedList<int> copy(SampleList);
            AssertContainsSampleRange(copy);
        }

        TEST_METHOD(CopyConstructor_WorksForEmptyLists)
        {
            LinkedList<int> copy(EmptyList);
            AssertEmpty(copy);
        }

        TEST_METHOD(Append_CopiesCorrectly)
        {
            LinkedList<int> anotherList;
            Fill(anotherList, SampleRangeEnd + 1, SampleRangeEnd + 10);
            SampleList.Append(anotherList);

            AssertSize(SampleList, SampleSize + 10);
            AssertContainsRange(SampleList, SampleRangeStart, SampleRangeEnd + 10);
        }

        TEST_METHOD(Append_AppendingAnEmptyListShouldPreserveTheOriginal)
        {
            SampleList.Append(EmptyList);            
            
            AssertSize(SampleList, SampleSize);
            AssertContainsRange(SampleList, SampleRangeStart, SampleRangeEnd);
        }

        TEST_METHOD(Append_AppendingToAnEmptyListShouldCopyCorrectly)
        {
            EmptyList.Append(SampleList);
            
            AssertContainsSampleRange(EmptyList);
        }

        TEST_METHOD(Append_AppendingEmptyToEmptyShouldWork)
        {
            EmptyList.Append(EmptyList);
            AssertEmpty(EmptyList);
        }

        TEST_METHOD(Head_CanActuallyModifyTheHead)
        {
            int newValue = SampleRangeStart - 1; // A value, which is not in the list

            SampleList.Front() = newValue;
            Assert::AreEqual(SampleList.Front(), newValue);

            SampleList.Front() = SampleRangeStart;
            Assert::AreEqual(SampleList.Front(), SampleRangeStart);

            AssertSize(SampleList, SampleSize); // make sure the operation does not resize the list
            AssertContainsSampleRange(SampleList); // make sure the operation does not work on a memory of its own
        }

		TEST_METHOD(HeadOperationsWorkCorrectly)
		{
			LinkedList<int> list;

            //
            // Add the numbers in the sample range and make sure that each time:
			// 1. the list size increases accordingly
            // 2. IsEmpty returns false
            // 3. The head can be retrieved
            // 4. The value of the head matches the value added
            //
            for (int i = SampleSize - 1; i >= 0; --i)
			{
                list.PushFront(SampleRangeStart + i);

				Assert::AreEqual(list.Front(), SampleRangeStart + i);
                AssertSize(list, SampleSize - i);
				Assert::IsFalse(list.IsEmpty());
			}

			// Make sure that the elements are there
            AssertContainsSampleRange(list);
            AssertSize(list, SampleSize);

			// Now remove all items, one by one, from the front
			for (int i = 0; i < SampleSize; ++i)
			{
                Assert::AreEqual(list.Front(), SampleRangeStart + i);
                AssertSize(list, SampleSize - i);
                Assert::IsFalse(list.IsEmpty());

				list.PopFront();
			}

            AssertEmpty(list);
		}

        TEST_METHOD(Tail_CanActuallyModifyTheTail)
        {
            int newValue = SampleRangeEnd + 1; // A value, which is not in the list

            SampleList.Back() = newValue;
            Assert::AreEqual(SampleList.Back(), newValue);

            SampleList.Back() = SampleRangeEnd;
            Assert::AreEqual(SampleList.Back(), SampleRangeEnd);

            AssertSize(SampleList, SampleSize); // make sure the operation does not resize the list
            AssertContainsSampleRange(SampleList); // make sure the operation does not work on a memory of its own
        }


		///
		///	Test tail operations
		///
		TEST_METHOD(TailOperationsWorkCorrectly)
		{
            LinkedList<int> list;

            //
            // Add the numbers in the sample range and make sure that each time:
            // 1. the list size increases accordingly
            // 2. IsEmpty returns false
            // 3. The back of the list can be retrieved
            // 4. The value of the back matches the value added
            //
            for (int i = 0; i < SampleSize; ++i)
            {
                list.PushBack(SampleRangeStart + i);

                Assert::AreEqual(list.Back(), SampleRangeStart + i);
                AssertSize(list, i + 1);
                Assert::IsFalse(list.IsEmpty());
            }

            // Make sure that the elements are there
            AssertContainsSampleRange(list);
            AssertSize(list, SampleSize);

            // Now remove all items, one by one, from the back
            for (int i = SampleSize - 1; i >= 0; --i)
            {
                Assert::AreEqual(list.Back(), SampleRangeStart + i);
                AssertSize(list, i + 1);
                Assert::IsFalse(list.IsEmpty());

                list.PopBack();
            }

            AssertEmpty(list);
		}

		///
		///	Test at index operations
		///
		TEST_METHOD(At_ReturnsCorrectValues)
		{
            const int TestSize = 5;

            LinkedList<int> list;

            Fill(list, 0, TestSize);

            for (int i = 0; i <= TestSize; ++i)
                Assert::AreEqual(list.At(i), i);
        }

        TEST_METHOD(At_AtInvalidIndexThrows)
        {
            Assert::ExpectException<std::out_of_range>(
                    [this]() { SampleList.At(SampleSize + 1); }
                );
        }

		///
		///	Test iterator functionality
		///
        TEST_METHOD(Iterator_CanCorrectlyReadTheList)
        {
            LinkedList<int>::Iterator it = SampleList.GetIterator();

            for (size_t i = 0; i < SampleSize; i++)
            {
                Assert::IsFalse(it.EndReached());
                Assert::AreEqual(it.GetCurrent(), SampleRangeStart + static_cast<int>(i));
                it.MoveNext();
            }

            // Assert that the iterator is at its end
            Assert::IsTrue(it.EndReached());

            // Now rewind and try again
            it.Rewind();

            for (size_t i = 0; i < SampleSize; i++)
            {
                Assert::IsFalse(it.EndReached());
                Assert::AreEqual(it.GetCurrent(), SampleRangeStart + static_cast<int>(i));
                it.MoveNext();
            }

            // Assert that the iterator is at its end
            Assert::IsTrue(it.EndReached());

            // The list should remain the same
            AssertContainsSampleRange(SampleList);
        }

        TEST_METHOD(Iterator_CanModifyTheList)
        {
            LinkedList<int>::Iterator it = SampleList.GetIterator();

			for (it.Rewind(); !it.EndReached(); it.MoveNext())
				it.SetCurrent(it.GetCurrent() + 100);

			AssertContainsRange(SampleList, SampleRangeStart + 100, SampleRangeEnd + 100);
		}
	};
}