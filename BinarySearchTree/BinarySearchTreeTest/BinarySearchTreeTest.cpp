#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../BinarySearchTree/BinarySearchTree.h"

#include <vector>
#include <algorithm>

namespace BinarySearchTreeTest
{		
	TEST_CLASS(EmptyTreeTest)
	{
        BinarySearchTree<int> emptyTree;

	public:
		
		TEST_METHOD(Size_IsZero)
		{
            Assert::AreEqual(emptyTree.Size(), (size_t)0);
		}

        TEST_METHOD(Empty_ReturnsTrue)
        {
            Assert::IsTrue(emptyTree.Empty());
        }
	};

    TEST_CLASS(NonEmptyTreeTest)
    {
        std::vector<int> sample{1, 10, -1, 50, 11};
        BinarySearchTree<int> tree;

    public:
        NonEmptyTreeTest()
        {
            for (auto it = sample.begin(); it != sample.end(); ++it)
                tree.Insert(*it);
        }

        int nonExistingElement()
        {
            return 1 + *std::max_element(sample.begin(), sample.end());
        }

        TEST_METHOD(Size_IsCorrect)
        {
            Assert::AreEqual(tree.Size(), sample.size());
        }

        TEST_METHOD(Empty_ReturnsFalse)
        {
            Assert::IsFalse(tree.Empty());
        }

        TEST_METHOD(Contains_ReturnsTrueForAllSampleElements)
        {
            for (auto it = sample.begin(); it != sample.end(); ++it)
                Assert::IsTrue(tree.Contains(*it));
        }

        TEST_METHOD(Contains_ReturnsFalseForNonExistingElement)
        {
            Assert::IsFalse(tree.Contains(nonExistingElement()));
        }

        TEST_METHOD(Remove_RemovesAllSampleElements)
        {
            size_t initialSize = tree.Size();

            for (auto it = sample.begin(); it != sample.end(); ++it)
            {
                tree.Remove(*it);
                Assert::IsFalse(tree.Contains(*it)); // the element should not be in the tree
                Assert::AreEqual(--initialSize, tree.Size()); // make sure the size changes accordingly
            }
        }

        TEST_METHOD(Remove_DoesNotChangeTheSizeForNonExistingElements)
        {
            size_t oldSize = tree.Size();
            tree.Remove(nonExistingElement());
            
            Assert::AreEqual(tree.Size(), oldSize);
        }

        TEST_METHOD(Clear_RemovesAllSampleElements)
        {
            tree.Clear();

            for (auto it = sample.begin(); it != sample.end(); ++it)
                Assert::IsFalse(tree.Contains(*it));
        }

        TEST_METHOD(Clear_SetsSizeToZero)
        {
            tree.Clear();
            Assert::AreEqual(tree.Size(), (size_t)0);
        }

        TEST_METHOD(Clear_EmptyReturnsTrue)
        {
            tree.Clear();
            Assert::IsTrue(tree.Empty());
        }

    };
}