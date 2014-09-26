#include <iostream>

#include "DynamicArray.h"


///
/// Създава нов динамичен масив
///
/// След инициализацията масивът е празен
/// (за него не е заделена динамична памет)
///
DynamicArray::DynamicArray()
{
	pData = NULL;
	AllocatedSize = 0;
	Length = 0;
}


///
/// Конструктор за копиране (copy constructor)
///
DynamicArray::DynamicArray(DynamicArray const & other)
{
	CopyFrom(other);
}


///
/// Оператор за присвояване (assignment operator)
///
DynamicArray& DynamicArray::operator=(DynamicArray const & other)
{
	if(this != &other)
	{
		Free();
		CopyFrom(other);
	}

	return *this;
}


///
/// Деструктор
///
DynamicArray::~DynamicArray()
{
	Free();
}


///
/// Копира данните от масива other в текущия обект
///
/// Функцията предполага, че масивът е празен.
/// Те не извършва действия за освобождаване на заетата памет.
/// Ако е нужно, преди нейното извикване трябва да се направи
/// обръщение към Free().
///
void DynamicArray::CopyFrom(DynamicArray const & other)
{
	pData = new int[other.AllocatedSize];

	for(size_t i = 0; i < other.Length; i++)
		pData[i] = other.pData[i];

	AllocatedSize = other.AllocatedSize;
	Length = other.Length;
}


///
/// Освобождава паметта заета от динамичния масив
///
void DynamicArray::Free()
{
	delete [] pData;

	pData = NULL;
	AllocatedSize = 0;
	Length = 0;
}


///
/// Преоразмерява динамичния масив, така че той да съдържа
/// NewSize елемента.
///
/// Ако NewSize е по-малко от текущия размер на масива,
/// елементите с индекси >= NewSize се губят.
///
void DynamicArray::Reallocate(size_t NewSize)
{
	int* pTemp = new int[NewSize];

	// колко елемента ще бъдат копирани
	size_t limit = std::min(AllocatedSize, NewSize);

	for(size_t i = 0; i < limit; i++)
		pTemp[i] = pData[i];

	delete [] pData;

	pData = pTemp;
	AllocatedSize = NewSize;
}


///
/// Добавя нов елемент в динамичния масив
///
/// Новият елемент се добавя в края на масива.
///
void DynamicArray::Add(int Element)
{
	if(Length >= AllocatedSize)
	{
		size_t NewSize = (AllocatedSize == 0 ? 2 : AllocatedSize*2);
		
		Reallocate(NewSize);
	}

	pData[Length++] = Element;
}


///
/// Връща размера на заетата от масива памет
///
size_t DynamicArray::GetAllocatedSize() const
{
	return AllocatedSize;
}


///
/// Връща броя на елементите в масива
///
size_t DynamicArray::GetLength() const
{
	return Length;
}


///
/// Връща елемента намиращ се на позиция index в масива
///
/// Ако index не е валиден индекс в масива, функцията
/// хвърля изключение от тип out_of_range
///
int DynamicArray::GetAt(size_t index) const
{
	if(index >= Length)
		throw std::out_of_range("index out of range!");

	return pData[index];
}


///
/// Променя стойността на елемент в масива.
///
/// Ако index не е валиден индекс в масива, функцията
/// хвърля изключение от тип out_of_range
///
void DynamicArray::SetAt(size_t index, int value)
{
	if(index >= Length)
		throw std::out_of_range("index out of range!");

	pData[index] = value;
}


///
/// Извежда информация за масива в STDOUT
///
void DynamicArray::Print() const
{
	std::cout
		<< "Dynamic Array at 0x" << this
		<< ", buffer at 0x"      << pData
		<< ", size ("            << Length
		<< " / "                 << AllocatedSize
		<< ")\n";

	if(Length > 0)
	{
		std::cout << "Contents: " << pData[0];

		for(size_t i = 1; i < Length; i++)
			std::cout << ", " << pData[i];

		std::cout << "\n";
	}
}


///
/// Генерира нов масив - конкатенация на текущия масив и rhs
///
DynamicArray DynamicArray::operator+ (DynamicArray const& rhs) const
{
	DynamicArray temp(*this);

	for(size_t i = 0; i < rhs.GetLength(); i++)
	{
		temp.Add(rhs.GetAt(i));
	}

	return temp;
}


///
/// Връща proxy обект, който представя елемента на масива с индекс index.
///
/// Тази версия на оператора се използва за неконстантни масиви и връща
/// proxy обект, който може да се използва за промяна на клетките на масива.
///
/// ВАЖНО:
/// 1. Операторът не прави проверка за това дали index
/// е валиден индекс в масива. Такава проверка се прави
/// всеки път, когато proxy обектът се използва.
/// 2. proxy обектът е свързан с конкретен индекс, а не с конкретен елемент
/// на масива. Това означава, че независимо от това какви промени се правят
/// в динамичния масив, proxy обектът винаги ще реферира един и същ индекс.
///
DynamicArrayElementProxy DynamicArray::operator[](size_t index)
{
	return DynamicArrayElementProxy(this, index);
}


///
/// Връща proxy обект, който представя елемента на масива с индекс index.
///
/// Тази версия на оператора се използва за константни масиви и връща
/// константен proxy обект, който *не може* да се използва за промяна
/// на клетките на масива.
///
/// За допълнителна информация, вижте бележките към неконстантната версия
/// на subscript оператора.
///
const DynamicArrayElementProxy DynamicArray::operator[](size_t index) const
{
	// По-долу е нужен const_cast, защото конструкторът на proxy-то
	// приема указател към неконстантен обект
	return DynamicArrayElementProxy(const_cast<DynamicArray*>(this), index);
}



/// ============================================================================



///
/// Конструира нов proxy обект, който представя
/// елемента на позиция ElementIndex в динамичния масив
/// сочен от pParent
///
DynamicArrayElementProxy::DynamicArrayElementProxy(DynamicArray * pDynamicArray, size_t ElementIndex) :
	pParent(pDynamicArray),
	ParentElementIndex(ElementIndex)
{
}


///
/// Връща стойността на елемента, когато той се
/// използва като rvalue
///
DynamicArrayElementProxy::operator int() const
{
	return pParent->GetAt(ParentElementIndex);
}


///
/// Присвоява нова стойност на елемента, когато
/// той се използва като lvalue
///
DynamicArrayElementProxy& DynamicArrayElementProxy::operator=(int value)
{
	pParent->SetAt(ParentElementIndex, value);

	return *this;
}