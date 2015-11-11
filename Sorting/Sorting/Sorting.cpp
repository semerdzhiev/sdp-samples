/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <algorithm>
#include <stack>
#include <assert.h>

///
/// Ако b < a, функцията разменя техните стойности
///
template <class T>
void swapif(T& a, T& b)
{
	if( b < a )
	{
		T temp(a);
		a = b;
		b = temp;
	}
}


///
/// Пряка селекция (Selection Sort)
///
template <class T>
void SelectionSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	for(size_t i = 0; i < Size-1; i++)
	{
		size_t min = i;

		for(size_t j = i+1; j < Size; j++)
		{
			if(pArr[j] < pArr[min])
				min = j;
		}

		swapif(pArr[i], pArr[min]);
	}
}


///
/// Метод на мехурчето (Bubble Sort)
///
template <class T>
void BubbleSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	for(size_t i = 0; i < Size-1; i++)
	{
		for(size_t j = Size-1; j > i; j--)
		{
			swapif(pArr[j-1], pArr[j]);
		}
	}
}


///
/// Сортиране чрез клатене (Shaker Sort)
///
template <class T>
void ShakerSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	size_t left = 0;
	size_t right = Size-1;

	while(left < right)
	{
		for(size_t r = right; r > left; r--)
			swapif(pArr[r-1], pArr[r]);

		left++; // защото най-малкият елемент от това обхождане вече е на своето място

		for(size_t l = left+1; l <= right; l++)
			swapif(pArr[l-1], pArr[l]);

		right--; // защото най-големият елемент от това обхождане вече е заел своето място
	}
}


///
/// Функция, която връща ключа на някакъв произволен тип.
///
///	За улеснение тук предполагаме, че типът е сводим до int
///
template <class T>
int key(T& value)
{
	return static_cast<int>(value);
}


///
/// Броене на честоти за масив с елементи, които са сводими то int.
///
/// Предполага се, че когато преобразуваме елемент до int,
/// се получава стойност, която е естествено число - неговият ключ.
///
template <class T>
void DistributionCounting(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	// Намираме най-големия ключ в масива
	int maxN = 0;

	for(size_t i = 0; i < Size; i++)
	{
		int nextKey = key(pArr[i]);

		if(maxN < nextKey)
			maxN = nextKey;
	}

	// В този масив ще пазим позициите, от които започва дадена поредица от елементи
	// във вече сортирания масив
	// (maxN също трябва да бъде валиден индекс в масива!)
	size_t * pEndsAt = new size_t[maxN + 1];

	for(int i = 0; i <= maxN; i++) // най-напред нулираме стойностите
		pEndsAt[i] = 0;

	// Сега броим честотите на срещане на елементите
	for(size_t i = 0; i < Size; i++)
	{
		pEndsAt[key(pArr[i])]++;
	}

	// Вече можем да определим позициите, от които започва всяка поредица от елементи:
	for(int i = 1; i <= maxN; i++)
	{
		pEndsAt[i] += pEndsAt[i-1];
	}

	// Сега сортираме стойностите в нов масив:
	T* pSorted = new T[Size];

	// ВАЖНО: for(size_t i = Size; myi >= 0; myi--)
	//	никога няма да завърши!

	size_t j = Size;

	while(j--)
	{
		size_t pos = --pEndsAt[key(pArr[j])];
		pSorted[pos] = pArr[j];
	}

	// Копираме сортирания масив обратно в оригиналния
	for(size_t i = 0; i < Size; i++)
	{
		pArr[i] = pSorted[i];
	}

	delete [] pSorted;
	delete [] pEndsAt;
}


///
/// Броене на честоти за масив с елементи – естествени числа
///
/// Тази разчита на това, че числата в масива са обекти без идентичност.
/// В случая това означава, че след като бъде направено преброяване,
/// данните в оригиналния масив вече не са необходими и функцията може
/// сама да генерира нужните данни в резултата.
///
template <> void DistributionCounting<int>(int* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	// Намираме най-голямото число в масива
	int maxN = 0;

	for(size_t i = 0; i < Size; i++)
	{
		if(maxN < pArr[i])
			maxN = pArr[i];
	}

	// В този масив ще пазим броя на срещаният на всеки елемент
	// (maxN също трябва да бъде валиден индекс в масива!)
	size_t * pCounts =  new size_t[maxN + 1];

	for(int i = 0; i <= maxN; i++) // нулираме стойностите
		pCounts[i] = 0;

	// Броим честотите на срещане на елементите
	for(size_t i = 0; i < Size; i++)
	{
		pCounts[pArr[i]]++;
	}

	// Поставяме елементите на правилните им места в масива
	size_t pos = 0;

	for(int i = 0; i <= maxN; i++)
	{
		while(pCounts[i] > 0)
		{
			pArr[pos++] = i;
			pCounts[i]--;
		}
	}

	delete [] pCounts;
}



///
/// Сортиране чрез вмъкване (Insertion Sort)
///
template <class T>
void InsertionSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	// Преместваме минималният елемент най-отпред
	for(size_t i = Size-1; i > 0; i--)
	{
		swapif(pArr[i-1], pArr[i]);
	}

	// Сега изпълняваме стъпките на сортирането
	for(size_t i = 2; i < Size; i++)
	{
		T value(pArr[i]);
		size_t j = i;
		
		while(pArr[j-1] > value)
		{
			pArr[j] = pArr[j-1];
			j--;
		}

		pArr[j] = value;
	}
}


///
/// h-сортира елементите на pArr,
/// които се намират на позиции k, k+h, k+2h, ...
///
template <class T>
void ShellSortH(T* pArr, size_t Size, size_t k, size_t h)
{
	// h-сортиране на pArr на позиции k, k+h, k+2h, ...
	// е идентино с h-сортиране на pArr + k на позиции 0, h, 2h, ...
	pArr = pArr + k;
	Size = Size - k; // нужно, за да запазим същата дясна граница

	// Намираме най-големия индекс Ai = i*h, такъв че Ai < Size
	size_t LastElement = (Size / h) * h - 1;

	size_t i;

	// Преместваме най-малкия елемент най-отпред
	for(i = LastElement; i > 0; i-=h)
	{
		assert( 0 <= i && i < Size);
		assert( 0 <= (i-h) && (i-h) < Size);
		swapif(pArr[i-h], pArr[i]);
	}

	assert(i == 0);

	// Сега h-сортираме елементите на позиции 0, h, 2h, ...
	for(size_t i = h; i < Size; i+=h)
	{
		assert( 0 <= i && i < Size);

		T value(pArr[i]);
		size_t j = i;
		
		while(pArr[j-h] > value)
		{
			assert( 0 <= j && j < Size);
			pArr[j] = pArr[j-h];
			j-=h;
		}

		assert( 0 <= j && j < Size);

		pArr[j] = value;
	}
}


///
/// Сортировка на Шел (Shell Sort)
///
template <class T>
void ShellSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	size_t h = 1;

	// determine the steps to be used for sorting
	while(h < Size / 9)
		h = h*3 + 1;

	for( ; h > 0; h = (h - 1) / 3 )
	{
		for(size_t i = 0; i < h; i++)
		{
			ShellSortH(pArr, Size, i, h);
		}
	}
}


///
/// Бързо сортиране (Quicksort)
///
template <class T>
void QuickSort(T* pArr, size_t Size)
{
	if(Size <= 1 || !pArr)
		return;

	size_t pos = Partition(pArr, Size);

	QuickSort(pArr, pos);
	QuickSort(pArr + pos + 1, Size - pos - 1);
}


///
/// Итеративна версия на бързо сортиране (Quicksort)
///
template <class T>
void QuickSortIterative(T* pArr, size_t Size)
{
	if (Size <= 1 || !pArr)
		return;

	std::stack<size_t> st;

	// Добавяме началото и края на масива в стека
	st.push(Size);
	st.push(0);

	size_t start, end, length;

	while (!st.empty())
	{
		// Изваждаме началото и края на следващото парче от масива,
		// което ще се обработва и намираме дължината му
		start = st.top();
		st.pop();
		end = st.top();
		st.pop();

		length = end - start;

		// Ако дължината е по-голяма от 1, изпълняваме един pass
		if(length > 1)
		{
			size_t pos = Partition(pArr + start, length);
			
			// Начало и край на лявата част
			st.push(start + pos);
			st.push(start);

			// Начало и край на дясната част
			st.push(end);
			st.push(start + pos + 1);
		}
	}
}


///
/// Изпълнява един pass на бързото сортиране (Quicksort)
///
/// \return
///    Индексът на елемента, който разделя двата
///    новополучени масива.
///
template <class T>
size_t Partition(T* pArr, size_t Size)
{
	assert(Size >= 2);

	// Методът Median-of-3 може да се използва ако масивър има поне 3 елемента.
	// Ако имаме само два елемента, прилагаме swapif и връщаме 1.
	if(Size == 2)
	{
		swapif(pArr[0], pArr[1]);
		return 1;
	}

	// Избираме елемент с Median-of-3
	size_t middle = Size / 2;
	swapif(pArr[0], pArr[middle]);
	swapif(pArr[0], pArr[Size-1]);
	swapif(pArr[middle], pArr[Size-1]);

	std::swap(pArr[middle], pArr[Size-2]);

	T& partitioningElement = pArr[Size-2];

	// Сега изпълняваме една итерация на QuickSort
	size_t left = 0;
	size_t right = Size-2;

	while(true)
	{
		while(pArr[++left] < partitioningElement)
			;

		while(pArr[--right] > partitioningElement)
		{
			if(left == right)
				break;
		}

		if(left >= right)
			break;

		std::swap(pArr[left], pArr[right]);
	}

	std::swap(pArr[left], partitioningElement);

	return left;
}


///
///	Пирамидално сортиране (Heap Sort)
///
template <class T>
void HeapSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	size_t i = Size / 2;

	while(i--)
	{
		Sift(pArr, i, Size);
	}


	i = Size;

	while(--i)
	{
		std::swap(pArr[0], pArr[i]);
		Sift(pArr, 0, i);
	}
}


///
/// Пресяване
///
template <class T>
void Sift(T* pArr, size_t pos, size_t Size)
{
	// Взимаме елемента, който трябва да се позиционира
	T elem(pArr[pos]);

	size_t ni = pos; // индекс на текущ възел
	size_t si = pos*2+1; // индекс на текущ наследник

	while(si < Size)
	{
		// в момента succ е индексът на левия наследник.
		// ако има десен наследник и той е по-голям,
		// трябва да преместим succ
		if(si < Size-1 && pArr[si] < pArr[si + 1])
			si++;

		// Вече succ e позицията на по-големия от двата наследника

		// Ако елементът, който местим е по-голям от по-големия наследник,
		// приключваме работата
		if(elem > pArr[si])
			break;

		pArr[ni] = pArr[si];
		ni = si;
		si = si * 2 + 1;
	}

	pArr[ni] = elem;
}


///
///	Сортиране чрез сливане (Merge Sort)
///
template <class T>
void MergeSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	T* pBuffer = new T[Size];

	MergeSortStep(pArr, Size, pBuffer);

	delete []  pBuffer;
}

template <class T>
void MergeSortStep(T* pArr, size_t Size, T* pBuffer)
{
	if(Size <= 1)
		return;

	size_t middle = Size / 2;

	MergeSortStep(pArr, middle, pBuffer);

	MergeSortStep(pArr + middle, Size - middle, pBuffer + middle);

	Merge(pArr, middle, pArr + middle, Size - middle, pBuffer);

	for(size_t i = 0; i < Size; i++)
		pArr[i] = pBuffer[i];
}

///
///	Слива съдържанието на двата сортирани масива pA и pB
///	в масива pResult.
///
///	Масивът получен при сливането също е сортиран.
///	В pResult трябва да има поне sizeA + sizeB елемента,
///	за да може да побере в себе си резултата от сливането.
///
template <class T>
void Merge(T* pA, size_t sizeA, T* pB, size_t sizeB, T* pResult)
{
	size_t i = 0; 
	size_t ia = 0;
	size_t ib = 0;

	while(ia < sizeA && ib < sizeB)
		pResult[i++] = (pA[ia] < pB[ib] ? pA[ia++] : pB[ib++]);

	while(ia < sizeA)
		pResult[i++] = pA[ia++];

	while(ib < sizeB)
		pResult[i++] = pB[ib++];
}


///
///	Сортиране чрез сливане (отдолу-нагоре)
///
template <class T>
void BottomUpMergeSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	T* pBuffer = new T[Size];

	// За да избегнем ненужните копирания, ще използваме два
	// указателя и масивите ще разменят ролите си.
	T* pRead = pArr;
	T* pWrite = pBuffer;

	// В цикъла използваме нарастващ размер на сортираните парчета от масива:
	// 1, 2, 4, 8, 16, ...
	for(size_t step = 1; step < Size; step *= 2)
	{
		for(size_t leftA = 0; leftA < Size; leftA += 2*step)
		{
			size_t rightA = std::min(leftA + step - 1, Size - 1);
			size_t leftB = rightA + 1;
			size_t rightB = std::min(leftB + step - 1, Size - 1);

			// Дотук имаме:
			//    leftA  <= Size-1 - валиден индекс в масива
			//    rightA <= Size-1 - валиден индекс в масива
			//    leftA  <= rightA - следователно размерът на частта от масива между
			//                       leftA и rightA е поне 1
			//    leftB  <= Size - следователно е или валиден индекс в масива или точно на
			//                     една позиция след последния елемент
			//    rightB <= Size-1 - ако leftB е валиден индекс в масива имаме leftB <= rightB
			//                       ако leftB == Size, то rightB == Size-1

			size_t sizeA = (rightA - leftA) + 1; // 1 или повече
			size_t sizeB = (rightB - leftB) + 1; // 0, ако leftB е извън масива

			Merge(pRead + leftA,
				  sizeA,
				  pRead + leftB,
				  sizeB,
				  pWrite + leftA);
		}

		// Разменяме ролите на двата масива
		std::swap(pRead, pWrite);
	}

	// Ако последната итерация е записала резултата от сливането в pBuffer,
	// а не в pArr, трябва да копираме елементите.
	// ВАЖНО: Понеже разменянето на двата указателя се изпълнява при всяко
	// преминаване през цикъла, условието не е pWrite != pArr,
	// а pWrite != pBuffer
	if(pWrite != pBuffer)
	{
		for(size_t i = 0; i < Size; i++)
			pArr[i] = pBuffer[i];
	}

	delete [] pBuffer;
}


//
// Инстанцираме шаблоните за работа с double
//
template void swapif<double>(double& a, double& b);
template void SelectionSort<double>(double* pArr, size_t Size);
template void BubbleSort<double>(double* pArr, size_t Size);
template void ShakerSort<double>(double* pArr, size_t Size);
template int key<double>(double& value);
template void DistributionCounting<double>(double* pArr, size_t Size);
template void InsertionSort<double>(double* pArr, size_t Size);
template void ShellSortH<double>(double* pArr, size_t Size, size_t k, size_t h);
template void ShellSort<double>(double* pArr, size_t Size);
template void QuickSort<double>(double* pArr, size_t Size);
template void QuickSortIterative<double>(double* pArr, size_t Size);
template size_t Partition<double>(double* pArr, size_t Size);
template void HeapSort<double>(double* pArr, size_t Size);
template void Sift<double>(double* pArr, size_t pos, size_t Size);
template void MergeSort<double>(double* pArr, size_t Size);
template void MergeSortStep<double>(double* pArr, size_t Size, double* pBuffer);
template void Merge<double>(double* pA, size_t sizeA, double* pB, size_t sizeB, double* pResult);
template void BottomUpMergeSort<double>(double* pArr, size_t Size);
