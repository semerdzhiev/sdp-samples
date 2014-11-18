#include <iostream>
#include <iomanip>

#include "UnitTestFramework.h"
#include "..\Stack\FixedSizeStack.h"


///
/// Проверява какво ще се случи ако опитаме
/// да извадим елемент от празния стек
///
TEST_FUNCTION(TestPopOnEmptyStack)
{
	FixedSizeStack stack(10);
	double foo;

	TEST(stack.Pop(foo) == false);
}

///
/// Проверява дали елементите, които добавяме
/// в стека излизат в правилния ред, а също и дали
/// можем да добавим и след това извадим точно толкова
/// елементи, колкото е размерът на стека
///
TEST_FUNCTION(TestCorrectSequence)
{
	const size_t SIZE = 10;

	FixedSizeStack stack(SIZE);
	double foo;

	for (double i = 1; i <= SIZE; i++)
	{
		std::cout << "     Adding " << i << std::endl;
		TEST(stack.Push(i));
	}

	for (double j = SIZE; j > 0; j--)
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
/// Проверява дали в стека може да се добавят 1 милион елемента
///
TEST_FUNCTION(Test1mElements)
{
	const size_t SIZE = 1000000;

	FixedSizeStack stack(SIZE);

	for (size_t i = 0; i < SIZE; i++)
		TEST(stack.Push(i));
}