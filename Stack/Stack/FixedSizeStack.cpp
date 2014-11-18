#include <assert.h>
#include "FixedSizeStack.h"


///
/// Конструктор по подразбиране
///
FixedSizeStack::FixedSizeStack(size_t Size)
{
	Init();
	pData = new double[Size];
	Allocated = Size;
}


///
/// Конструктор за копиране
///
FixedSizeStack::FixedSizeStack(FixedSizeStack const & Other)
{
	Init();
	CopyFrom(Other);
}


///
/// Деструктор
///
FixedSizeStack::~FixedSizeStack()
{
	Destroy();
}


///
/// Оператор за присвояване
///
FixedSizeStack& FixedSizeStack::operator=(FixedSizeStack const & Other)
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
void FixedSizeStack::Init()
{
	pData = 0;
	Allocated = 0;
	Used = 0;
}


///
/// Изпразва стека и освобождава заетата от него памет
///
void FixedSizeStack::Destroy()
{
	delete [] pData;
	Init();
}


///
/// Създава копие на друг стек
///
/// Функцията предполага, че обектът е празен
/// (за елементите не е била заделяна памет)
///
/// \param [in] element
///		Друг обект, чиито данни трябва да се копират
///
void FixedSizeStack::CopyFrom(FixedSizeStack const& Other)
{
	pData = new double[Other.Allocated];
	Allocated = Other.Allocated;
	Used = Other.Used;

	for (size_t i = 0; i < Used; i++)
		pData[i] = Other.pData[i];
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
bool FixedSizeStack::Push(double element)
{
	if (Used >= Allocated)
		return false;

	pData[Used++] = element;
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
bool FixedSizeStack::Pop(double& element)
{
	if (Used == 0)
		return false;

	element = pData[Used - 1];
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
double FixedSizeStack::Peek() const
{
	assert(Used != 0);

	return pData[Used - 1];
}


///
/// Връща максималната вместимост на стека в брой елементи
///
size_t FixedSizeStack::GetAllocatedSize() const
{
	return Allocated;
}


///
/// Връща броя на съхранените в стека елементи
///
size_t FixedSizeStack::GetUsedSize() const
{
	return Used;
}


///
/// Проверява дали стекът е празен
///
bool FixedSizeStack::IsEmpty() const
{
	return Used != 0;
}