#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Stack\FixedSizeStack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackTestVs
{		
	TEST_CLASS(AClassThatTestsStacks)
	{
	public:
		
		TEST_METHOD(FixedStack_PopOnEmptyStack)
		{
			FixedSizeStack stack(5);
			double foo;
			Assert::IsFalse(stack.Pop(foo));
		}

		TEST_METHOD(FixedStack_Add1mElements)
		{
			FixedSizeStack stack(10000);

			for (double i = 0; i < 10000; i++)
				Assert::IsTrue(stack.Push(i));
		}

		TEST_METHOD(FixedStack_TestCorrectSequence)
		{
			const size_t ELEMENTS_COUNT = 10;
			
			FixedSizeStack stack(ELEMENTS_COUNT);

			double foo;

			for (double i = 1; i <= ELEMENTS_COUNT; i++)
			{
				Assert::IsTrue(stack.Push(i));
			}

			for (double j = ELEMENTS_COUNT; j > 0; j--)
			{
				Assert::IsTrue(stack.Peek() == j);
				Assert::IsTrue(stack.Pop(foo));
				Assert::AreEqual(foo, j);
			}
		}
	};
}