#include <iostream>

#include "Sorting.h"

///
/// Показва съдържанието на pArr
///
template <class SAMPLE_TYPE>
void PrintArray(const SAMPLE_TYPE* pArr, size_t Size)
{
	if (Size == 0)
	{
		std::cout << "(empty)\n";
	}
	else
	{
		std::cout << pArr[0];

		for (size_t i = 1; i < Size; i++)
		{
			std::cout << ", " << pArr[i];
		}
	}
}


///
/// Тества поведението на една сортираща функция
///
/// \param [in] pfnSort
///     Указател към функцията, която ще се тества
///
/// \param [in] Name
///     Името на функцията, която ще се тества
///     Това е просто текст, който ще се изведе на екрана,
///		за да се знае какво се обработва в момента и няма отношение
///		към работата на функцията.
///
template <class SAMPLE_TYPE>
void TestSortingFunction(void pfnSort(SAMPLE_TYPE*, size_t), const char* Name)
{
	SAMPLE_TYPE DataSamples[][10] = {
			{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
			{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
			{ 1, 0, 3, 2, 5, 4, 7, 6, 9, 8 },
			{ 1, 9, 6, 7, 1, 3, 2, 1, 5, 0 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 }
	};

	const int SampleSize = 10;
	const int SamplesCount = 6;

	// Извеждаме информация за тестовете
	std::cout << "Testing " << Name;
	std::cout << "\n    Samples: " << SamplesCount;
	std::cout << "\n    Sample size: " << SampleSize;
	std::cout << "\n    Samples:";

	for (int i = 0; i < SamplesCount; i++)
	{
		std::cout << "\n        Sample " << i << ": ";
		PrintArray<SAMPLE_TYPE>(DataSamples[i], SampleSize);
	}

	// Изпълняваме тестовете
	std::cout << "\n\n    Sorting results:";

	for (int i = 0; i < SamplesCount; i++)
	{
		pfnSort(DataSamples[i], SampleSize);
		std::cout << "\n        Sorted " << i << ": ";
		PrintArray(DataSamples[i], SampleSize);
	}

	std::cout << "\n    [end]\n\n\n";
}

///
/// Провежда тестове за една функция, като се указва и типът на данните (int или double)
///
#define TEST(x, SAMPLE_TYPE) TestSortingFunction<SAMPLE_TYPE>(x, #x)

int main()
{
	TEST(SelectionSort, double);
	TEST(BubbleSort, double);
	TEST(ShakerSort, double);
	TEST(DistributionCounting, int);
	TEST(DistributionCounting, double);
	TEST(InsertionSort, double);
	TEST(ShellSort, double);
	TEST(QuickSort, double);
	TEST(HeapSort, double);
	TEST(MergeSort, double);
	TEST(BottomUpMergeSort, double);
}