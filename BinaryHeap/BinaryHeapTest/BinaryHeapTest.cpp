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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../BinaryHeap/BinaryHeap.h"

#include <vector>
#include <algorithm>

namespace BinaryHeapTest
{		
	TEST_CLASS(BinaryHeapTest)
	{
	public:
		
        TEST_METHOD(Insert_KeepsTheMinimalElementOnTop)
        {
            BinaryHeap<int> heap;
            std::vector<int> v{ 1, 5, -1, 11, 23, 48, 73 };

            for (auto it = v.begin(); it != v.end(); ++it)
            {
                heap.Insert(*it);
                Assert::AreEqual(heap.Top(), *std::min_element(v.begin(), it+1));
            }
        }

        TEST_METHOD(ExtractRemovesItemsInProperSequence)
        {
            BinaryHeap<int> heap;
            std::vector<int> v{ 1, 5, -1, 11, 23, 48, 73 };

            for (auto it = v.begin(); it != v.end(); ++it)
                heap.Insert(*it);

            std::sort(v.begin(), v.end());

            for (auto it = v.begin(); it != v.end(); ++it)
            {
                Assert::AreEqual(heap.Top(), *it);
                heap.Extract();
            }
        }
	};
}