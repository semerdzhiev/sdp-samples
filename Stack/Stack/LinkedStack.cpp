/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <assert.h>
#include <exception>
#include "LinkedStack.h"


///
/// Конструктор по подразбиране за двойната кутия
///
LinkedStack::Box::Box(double Data, Box* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
}


///
/// Конструктор по подразбиране
///
LinkedStack::LinkedStack()
{
	Init();
}


///
/// Конструктор за копиране
///
/// \exception std::bad_alloc
///		Ако копирането не приключи успешно
///
LinkedStack::LinkedStack(LinkedStack const & Other)
{
	Init();
	CopyFrom(Other); // CopyFrom почиства след себе си,
					 // ако копирането е неуспешно
}


///
/// Деструктор
///
LinkedStack::~LinkedStack()
{
	Destroy();
}


///
/// Оператор за присвояване
///
/// Операторът е реализиран така, че първо освобождава
/// паметта заета от стека и след това копира данните.
///
/// Ако копирането не приключи успешно,
/// функцията почиства и стекът ще бъде празен.
///
/// \exception std::bad_alloc
///		Ако копирането не приключи успешно
///
LinkedStack& LinkedStack::operator=(LinkedStack const & Other)
{
	if (this != &Other)
	{
		Destroy();
		CopyFrom(Other);
	}

	return *this;
}


///
/// Задава начални стойности на член-данните на класа.
///
/// Стойностите предполагат, че стекът е празен и за
/// неговите елементи не е заделена памет.
///
void LinkedStack::Init()
{
	pTop = 0;
	Used = 0;
}


///
/// Изпразва стека и освобождава заетата от него памет
///
void LinkedStack::Destroy()
{
	Box* p;

	while (pTop)
	{
		p = pTop;
		pTop = pTop->pNext;
		delete p;
	}

	Init();
}


///
/// Копира съдържанието на друг стек
///
/// Функцията предполага, че обектът,
/// в който копираме е празен.
///
/// \param [in] element
///		Друг обект, чиито данни трябва да се копират
/// 
/// \exception std::bad_alloc
///		Ако заделянето на памет е било неуспешно
///
void LinkedStack::CopyFrom(LinkedStack const& Other)
{
	if (Other.IsEmpty())
		return;

	Box *ours, *theirs;

	// Създаваме копие на веригата от елементи в LinkedStack
	// Ако заделянето не е успешно, функцията почиства след себе си
	try
	{
		pTop = new Box(Other.pTop->Data);

		ours = pTop;
		theirs = Other.pTop->pNext;

		while (theirs)
		{
			ours->pNext = new Box(theirs->Data);
			ours = ours->pNext;
			theirs = theirs->pNext;
		}

		Used = Other.Used;
	}
	catch (std::bad_alloc&)
	{
		Destroy();	// Може да се извика, защото:
					// 1. pTop сочи към върха на клонираната верига
					// 2. Заделяме кутиите, така че последната кутия във веригата
					//    има pNext == NULL
		throw;
	}
}


///
/// Добавя нов елемент на върха на стека
///
/// \param [in] element
///		Елемент, който трябва да се добави
///
/// \return
///		true ако функцията успее и false в противен случай.
///
bool LinkedStack::Push(double element)
{
	Box* pNewBox;

	try {
		pNewBox = new Box(element, pTop);
	}
	catch(...) {
		return false;
	}

	pTop = pNewBox;
	Used++;
	return true;
}


///
/// Премахва и връща елемента, който се намира на върха на стека
///
/// \param [out] element
///		Функцията връща стойността на елемента в този параметър.
///		Ако стекът е празен, той не се променя.
///
/// \return
///		true ако функцията успее и false в противен случай.
///
bool LinkedStack::Pop(double& element)
{
	if (Used == 0)
		return false;

	element = pTop->Data;

	Box* pOld = pTop;
	pTop = pTop->pNext;
	delete pOld;
	
	Used--;

	return true;
}


///
/// Връща елемента, който се намира на върха на стека
///
/// Ако стекът е празен, функцията предизвиква assertion fault
///
/// \return
///		Стойността на елемента
///
double LinkedStack::Peek() const
{
	assert(Used != 0);

	return pTop->Data;
}


///
/// Премахва всички елементи от стека
///
/// Поради вътрешното представяне, тази функция
/// освобождава и паметта заета от стека.
///
void LinkedStack::RemoveAll()
{
	Destroy();
}


///
/// Връща максималната вместимост на стека в брой елементи
///
size_t LinkedStack::GetAllocatedSize() const
{
	return Used * sizeof(Box);
}


///
/// Връща броя на съхранените в стека елементи
///
size_t LinkedStack::GetSize() const
{
	return Used;
}


///
/// Проверява дали стекът е празен
///
bool LinkedStack::IsEmpty() const
{
	return Used == 0;
}