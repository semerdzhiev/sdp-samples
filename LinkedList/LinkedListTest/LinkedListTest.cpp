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
    class ListUtils
    {
    public:
        ///
        /// Checks whether list contains all integers in [First,Last].
        ///
        /// The integers should be stored in ascending order in the list.
        ///
        static bool ContainsRange(const LinkedList<int>& List, int First, int Last)
        {
            LinkedList<int>::Iterator it = List.GetIterator();

            int i = First;

            while (!it.EndReached() && i <= Last)
            {
                if (it.GetCurrent() != i)
                    break;

                i++;
                it.MoveNext();
            }

            return i > Last;
        }

        ///
        /// Fills a list with all integers in the interval [Start, End].
        ///
        static void Fill(LinkedList<int>& List, int First, int Last)
        {
            for (int i = First; i <= Last; i++)
                List.PushBack(i);
        }

        static void AssertEmpty(const LinkedList<int>& List)
        {
            Assert::IsTrue(List.IsEmpty());
            Assert::AreEqual(List.GetSize(), size_t(0));
        }

        static void AssertSize(const LinkedList<int>& List, size_t Size)
        {
            Assert::AreEqual(List.GetSize(), Size);
        }

        static void AssertContainsRange(const LinkedList<int>& List, int First, int Last)
        {
            Assert::IsTrue(ContainsRange(List, First, Last));
        }
    };

    class Range
    {
    public:
        const int First;
        const int Last;
        const int Size;

        Range(int First, int Last)
            : First(First), Last(Last), Size(Last - First + 1)
        {
        }

        void Fill(LinkedList<int>& List)
        {
            ListUtils::Fill(List, First, Last);
        }

        void AssertOn(LinkedList<int>& List)
        {
            ListUtils::AssertContainsRange(List, First, Last);
            ListUtils::AssertSize(List, Size);
        }
    };

    //
    // Tests the behavior of operations on one or more empty lists.
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

        TEST_METHOD(CopyConstructor_OnEmptyLists)
        {
            LinkedList<int> test(EmptyList);

            ListUtils::AssertEmpty(test);
        }

        TEST_METHOD(Assignment_BetweenEmptyLists)
        {
            LinkedList<int> test;
            test = EmptyList;

            ListUtils::AssertEmpty(test);
        }

        TEST_METHOD(Append_OnEmptyLists)
        {
            LinkedList<int> test;
            test.Append(EmptyList);

            ListUtils::AssertEmpty(test);
        }
    };

    TEST_CLASS(ListTest)
    {
    private:
        LinkedList<int> EmptyList;
        LinkedList<int> SampleList;
        Range SampleRange;

    public:
        ListTest()
            : SampleRange(1, 10)
        {
            // Uncomment the line below to see the order in which
            // the unit test framework invokes each method
            // Logger::WriteMessage(L"ListTest::ListTest()");
            SampleRange.Fill(SampleList);
        }

        // Uncomment the code below to see the order in which
        // the unit test framework invokes each method
        /*
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
        */

        TEST_METHOD(SelfCheck)
        {
            SampleRange.AssertOn(SampleList);
        }

        TEST_METHOD(Clear_EmptiesTheList)
        {
            SampleList.Clear();

            ListUtils::AssertEmpty(SampleList);
        }

        TEST_METHOD(Head_CanActuallyModifyTheHead)
        {
            int newValue = SampleRange.First - 1; // A value, which is not in the list

            SampleList.Front() = newValue;
            Assert::AreEqual(SampleList.Front(), newValue);

            SampleList.Front() = SampleRange.First;
            Assert::AreEqual(SampleList.Front(), SampleRange.First);

            SampleRange.AssertOn(SampleList); // The list should be restored to its initial state
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
            for (int i = SampleRange.Last; i >= SampleRange.First; --i)
            {
                list.PushFront(i);

                Assert::AreEqual(list.Front(), i);
                ListUtils::AssertSize(list, SampleRange.Last - i + 1);
                Assert::IsFalse(list.IsEmpty());
            }

            // Make sure that the elements are there
            SampleRange.AssertOn(list);

            // Now remove all items, one by one, from the front
            for (int i = SampleRange.First; i <= SampleRange.Last; ++i)
            {
                Assert::AreEqual(list.Front(), i);
                ListUtils::AssertSize(list, SampleRange.Last - i + 1);
                Assert::IsFalse(list.IsEmpty());

                list.PopFront();
            }

            ListUtils::AssertEmpty(list);
        }

        TEST_METHOD(Tail_CanActuallyModifyTheTail)
        {
            int newValue = SampleRange.Last + 1; // A value, which is not in the list

            SampleList.Back() = newValue;
            Assert::AreEqual(SampleList.Back(), newValue);

            SampleList.Back() = SampleRange.Last;
            Assert::AreEqual(SampleList.Back(), SampleRange.Last);

            SampleRange.AssertOn(SampleList); // The list should be restored to its initial state
        }


        ///
        ///    Test tail operations
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
            for (int i = SampleRange.First; i <= SampleRange.Last; ++i)
            {
                list.PushBack(i);

                Assert::AreEqual(list.Back(), i);
                ListUtils::AssertSize(list, i - SampleRange.First + 1);
                Assert::IsFalse(list.IsEmpty());
            }

            // Make sure that the elements are there
            SampleRange.AssertOn(list);

            // Now remove all items, one by one, from the back
            for (int i = SampleRange.Last; i >= SampleRange.First; --i)
            {
                Assert::AreEqual(list.Back(), i);
                ListUtils::AssertSize(list, i - SampleRange.First + 1);
                Assert::IsFalse(list.IsEmpty());

                list.PopBack();
            }

            ListUtils::AssertEmpty(list);
        }

        TEST_METHOD(At_ReturnsCorrectValues)
        {
            // We work with a small value here, because the loop has quadratic complexity
            const int MaxValue = 5;

            LinkedList<int> list;

            ListUtils::Fill(list, 0, MaxValue);

            for (int i = 0; i <= MaxValue; ++i)
                Assert::AreEqual(list.At(i), i);
        }

        TEST_METHOD(At_AtInvalidIndexThrows)
        {
            Assert::ExpectException<std::out_of_range>(
                [this]() { SampleList.At(SampleRange.Size + 1); }
            );
        }

        TEST_METHOD(CopyConstructor_CopiesCorrectly)
        {
            LinkedList<int> copy(SampleList);
            SampleRange.AssertOn(SampleList);
        }

        TEST_METHOD(AssignmentOperator_CreatesExactCopy)
        {
            LinkedList<int> list;
            Range range(20, 30);

            range.Fill(list);
            range.AssertOn(list);

            list = SampleList;

            SampleRange.AssertOn(list);
        }

        TEST_METHOD(AssignmentOperator_AssigningFromEmptyListErasesAllContent)
        {
            SampleList = EmptyList;
            ListUtils::AssertEmpty(SampleList);
        }

        TEST_METHOD(Append_TheEmptyListIsLeftIdentity)
        {
            // From the algebraic theory: for a given set S,
            // an element E in S is a left identity with respect to the operation *,
            // iff E * A = A, for all A in S

            EmptyList.Append(SampleList);
            SampleRange.AssertOn(EmptyList);
        }

        TEST_METHOD(Append_TheEmptyListIsRightIdentity)
        {
            SampleList.Append(EmptyList);
            SampleRange.AssertOn(SampleList);
        }

        TEST_METHOD(Append_CopiesCorrectly)
        {
            Range secondRange(SampleRange.Last + 1, SampleRange.Last + 10);
            LinkedList<int> secondList;

            secondRange.Fill(secondList);

            SampleList.Append(secondList);

            Range combinedRange(SampleRange.First, secondRange.Last);
            combinedRange.AssertOn(SampleList);
        }

        ///
        ///    Test iterator functionality
        ///
        TEST_METHOD(Iterator_CanCorrectlyIterate)
        {
            LinkedList<int>::Iterator it = SampleList.GetIterator();

            for (int i = SampleRange.First; i <= SampleRange.Last; ++i)
            {
                Assert::IsFalse(it.EndReached());
                Assert::AreEqual(it.GetCurrent(), i);
                it.MoveNext();
            }

            // Assert that the iterator is at its end
            Assert::IsTrue(it.EndReached());
        }

        TEST_METHOD(Iterator_CanRewind)
        {
            LinkedList<int>::Iterator it = SampleList.GetIterator();

            while (!it.EndReached())
                it.MoveNext();

            it.Rewind();

            Assert::AreEqual(it.GetCurrent(), SampleRange.First); // Must be at the start of list now
        }

        TEST_METHOD(Iterator_CanModifyTheList)
        {
            const int shiftBy = 100;
            Range shiftedRange(SampleRange.First + shiftBy, SampleRange.Last + shiftBy);

            LinkedList<int>::Iterator it = SampleList.GetIterator();

            for (; !it.EndReached(); it.MoveNext())
                it.SetCurrent(it.GetCurrent() + shiftBy);

            shiftedRange.AssertOn(SampleList);
        }
    };
}