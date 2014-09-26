#include <iostream>

///
/// Представя динамичен масив
///
struct DynamicArray
{
	/// Съдържанието на масива
	int *pData;

	/// Размер на заделената памет за масива
	size_t Size;
	
	/// Брой на използваните клетки от масива
	size_t Used;
};


///
/// Инициализира нов динамичен масив
///
/// След инициализацията масивът е празен
/// (за него не е заделена динамична памет)
///
void Init(DynamicArray* pArr)
{
	pArr->pData = NULL;
	pArr->Size = 0;
	pArr->Used = 0;
}


///
/// Освобождава паметта заета от динамичен масив
///
void Free(DynamicArray* pArr)
{
	delete [] pArr->pData;
	pArr->Size = 0;
	pArr->Used = 0;
}


///
/// Changes the size of a dynamic array to NewSize
///
void Reallocate(DynamicArray* pArr, size_t NewSize)
{
	int* pTemp = new int[NewSize];

	for(size_t i = 0; i < std::min(pArr->Size, NewSize); i++)
		pTemp[i] = pArr->pData[i];

	delete [] pArr->pData;

	pArr->pData = pTemp;
	pArr->Size = NewSize;
}


///
/// Добавя нов елемент в динамичен масив
///
void Add(DynamicArray* pArr, int Element)
{
	if(pArr->Used >= pArr->Size)
	{
		size_t NewSize = (pArr->Size == 0 ? 2 : pArr->Size*2);
		
		Reallocate(pArr, NewSize);
	}

	pArr->pData[pArr->Used++] = Element;
}


///
/// Извежда информация за динамичния масив в STDOUT
///
void PrintArrayStatus(DynamicArray* pda)
{
	std::cout
		<< "Array at 0x"   << pda
		<< " buffer at 0x" << pda->pData
		<< " size ("       << pda->Used
		<< " / "           << pda->Size
		<< ")\n";
}


int main()
{
	DynamicArray da;

	Init(&da);

	for(int i = 0; i < 100; i++)
	{
		PrintArrayStatus(&da);

		Add(&da, i);
	}

	PrintArrayStatus(&da);

	Free(&da);

	return 0;
}