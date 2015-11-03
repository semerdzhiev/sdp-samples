/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <iomanip>

#include "UnitTestFramework.h"
#include "..\Stack\LinkedStack.h"
#include "..\Stack\FixedSizeStack.h"


///
/// Проверява какво ще се случи ако опитаме
/// да извадим елемент от празния стек
///
template <class T>
void TestPopOnEmptyStack(T& stack)
{
	double foo;

	TEST(stack.Pop(foo) == false);
}


///
/// Провежда TestPopOnEmptyStack() върху FixedSizeStack
///
TEST_FUNCTION(FS_TestPopOnEmptyStack)
{
	FixedSizeStack stack(10);
	TestPopOnEmptyStack(stack);
}


///
/// Провежда TestPopOnEmptyStack() върху LinkedStack
///
TEST_FUNCTION(LS_TestPopOnEmptyStack)
{
	LinkedStack stack;
	TestPopOnEmptyStack(stack);
}


///
/// Проверява дали елементите, които добавяме
/// в стека излизат в правилния ред, а също и дали
/// можем да добавим и след това извадим точно толкова
/// елементи, колкото е размерът на стека
///
template <class T>
void TestCorrectSequence(T& stack, size_t ElementsCount)
{
	double foo;

	for (double i = 1; i <= ElementsCount; i++)
	{
		std::cout << "     Adding " << i << std::endl;
		TEST(stack.Push(i));
	}

	for (double j = ElementsCount; j > 0; j--)
	{
		std::cout << "     Poppping " << j << ": ";
		TEST(stack.Peek() == j);
		std::cout << "1";
		TEST(stack.Pop(foo));
		std::cout << "2";
		TEST(foo == j);
		std::cout << "3";
		std::cout << std::endl;
	}
}


///
/// Провежда TestCorrectSequence върху FixedSizeStack
///
TEST_FUNCTION(FS_TestCorrectSequence)
{
	const size_t SIZE = 10;
	FixedSizeStack stack(SIZE);
	TestCorrectSequence(stack, SIZE);	
}


///
/// Провежда TestCorrectSequence върху LinkedStack
///
TEST_FUNCTION(LS_TestCorrectSequence)
{
	const size_t SIZE = 10;
	LinkedStack stack;
	TestCorrectSequence(stack, SIZE);
}


///
/// Проверява дали в стека може да се добавят голям брой елементи
///
template <class T>
void TestCapacity(T& stack, size_t ElementsCount)
{
	for (size_t i = 0; i < ElementsCount; i++)
		TEST(stack.Push(i));
}


///
/// Провежда TestCapacity върху FixedSizeStack
/// с 1000000 елемента
///
TEST_FUNCTION(FS_Test1mElements)
{
	const size_t SIZE = 1000000;
	FixedSizeStack stack(SIZE);
	TestCapacity(stack, SIZE);
}


///
/// Провежда TestCapacity върху LinkedStack
/// с 1000000 елемента
///
TEST_FUNCTION(LS_Test1mElements)
{
	const size_t SIZE = 1000000;
	LinkedStack stack;
	TestCapacity(stack, SIZE);
}