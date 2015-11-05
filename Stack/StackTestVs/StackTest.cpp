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

#include "..\Stack\StaticStack.h"
#include "..\Stack\FixedSizeStack.h"
#include "..\Stack\LinkedStack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackTestVs
{
	///
	/// A pop on an emty stack should return false
	///
	template <class T> void TestEmptyStack(T& stack)
	{
		double foo;

		Assert::IsFalse(stack.Pop(foo));
	}

	///
	/// Checks whether stack provides proper FILO operations:
	/// 1. The elements are popped in reverse of the push order
	/// 2. The number of elements that can be popped is
	/// the same as the number of pushed elements
	/// 3. Peek works correctly after each push/pop
	///
	template <class T> void TestCorrectSequence(T& stack, size_t ElementsCount)
	{
		double value, popped;

		// Push the specified number of elements
		// and check Peek() and GetSize() on each step
		for (size_t i = 1; i <= ElementsCount; i++)
		{
			value = static_cast<double>(i);

			stack.Push(value);

			Assert::AreEqual(stack.Peek(), value, L"Peek incosistent after push");
			Assert::AreEqual(stack.GetSize(), i, L"Size inconsistent after push");
		}

		// Now pop the elements and check Peek() and
		// GetSize() on each step
		for (size_t j = ElementsCount; j > 0; j--)
		{
			value = static_cast<double>(j);

			Assert::AreEqual(stack.GetSize(), j, L"Size inconsistent before pop");
			Assert::AreEqual(stack.Peek(), value, L"Peek inconsistent before pop");
			Assert::IsTrue(stack.Pop(popped), L"Cannot pop");
			Assert::AreEqual(popped, value, L"Pop yielded incorrect value");
		}

		// The size of the stack should be zero and Pop should return false
		Assert::AreEqual(stack.GetSize(), size_t(0), L"Size not zero after popping all elements");
		Assert::IsFalse(stack.Pop(popped), L"Pop not false on empty stack");
	}


	TEST_CLASS(StackTest)
	{
	public:
		TEST_METHOD(StaticStack_EmptyStack)
		{
			TestEmptyStack(StaticStack<double, 10>());
		}

		TEST_METHOD(StaticStack_CorrectSequence)
		{
			TestCorrectSequence(StaticStack<double, 100>(), 100);
		}

		TEST_METHOD(FixedSizeStack_EmptyStack)
		{
			TestEmptyStack(FixedSizeStack<double>(10));
		}

		TEST_METHOD(FixedSizeStack_CorrectSequence)
		{
			TestCorrectSequence(FixedSizeStack<double>(100), 100);
		}

		TEST_METHOD(LinkedStack_EmptyStack)
		{
			TestEmptyStack(LinkedStack<double>());
		}

		TEST_METHOD(LinkedStack_CorrectSequence)
		{
			TestCorrectSequence(LinkedStack<double>(), 100);
		}
	};
}