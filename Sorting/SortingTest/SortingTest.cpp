#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Sorting\Sorting.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortingTest
{
	///
	/// Checks whether an array is sorted
	///
	/// The function assumes that the greater than operator (>)
	/// is defined for the type T
	///
	/// \return
	///		true if the array is sorted or empty (Size==0) or pArr==NULL
	///
	template <typename T>
	bool IsSorted(T* pArr, size_t Size)
	{
		if (Size == 0 || !pArr)
			return true;

		for (size_t i = 1; i < Size; i++)
		{
			if (pArr[i-1] > pArr[i])
				return false;
		}

		return true;
	}


	///
	/// Тества поведението на една сортираща функция върху
	/// примерни данни.
	///
	/// За целта се използват няколко предварително подготвени
	/// масива с числа, като функцията се прилага върху всеки от
	/// тях и след това се проверява дали са сортирани.
	///
	/// SAMPLE_TYPE може да бъде произволен числов тип в C++
	/// (например int, unsigned int, float, double)
	///
	/// \param [in] pfnSort
	///     Указател към функцията, която ще се тества
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunctionOnSamples(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		// Размерът на тестовите данни има значение.
		// Ако опитате да проведете тестовете с така дадения размер (10)
		// и анализирате каква част от кода е покрита от unit test-овете,
		// ще откриете, че в BottomUpMergeSort, не се преминава през
		// клаузата, която следи за случаите, в които
		// последната итерация е записала резултата от сливането в pBuffer,
		// а не в pArr.
		// Има различни начини, по които може да се реши този проблем.
		// Например можем да тестваме функциите с масиви с такива размери,
		// че BottomUpMergeSort да мине през нечетен брой итерации на външния цикъл
		// (например ако го оставим да работи върху масив с размер между 4 и 8).

		SAMPLE_TYPE DataSamples[][10] = {
				{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
				{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
				{ 1, 0, 3, 2, 5, 4, 7, 6, 9, 8 },
				{ 1, 9, 6, 7, 1, 3, 2, 1, 5, 0 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 2, 1, 2, 1, 2, 1, 2, 1, 2 }
		};

		const int SampleSize = 10; // Ако го направим например на 7,
		                           // ще подобрим покритието на BottomUpMergeSort

		const int SamplesCount = 6;

		for (int i = 0; i < SamplesCount; i++)
		{
			pfnSort(DataSamples[i], SampleSize);
			Assert::IsTrue(IsSorted(DataSamples[i], SampleSize));
		}
	}

	///
	/// Тества поведението на една сортираща функция върху
	/// NULL pointer.
	///
	/// Тества се поведението на функцията при подаден
	/// NULL pointer и размер на масив равен на нула, както
	/// и подаден NULL pointer и размер различен от нула.
	///
	/// SAMPLE_TYPE може да бъде произволен числов тип в C++
	/// (например int, unsigned int, float, double)
	///
	/// \param [in] pfnSort
	///     Указател към функцията, която ще се тества
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunctionOnNull(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		pfnSort(NULL, 100);
		pfnSort(NULL, 0);
	}

	///
	/// Тества поведението на една сортираща функция при
	/// размер 0 на подадения масив
	///
	/// Тества се поведението на функцията при подадена
	/// стойност 0 на размерана входния масив
	///
	/// \param [in] pfnSort
	///     Указател към функцията, която ще се тества
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunctionOnZeroSize(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		SAMPLE_TYPE Sample[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		
		pfnSort(Sample, 0);
		pfnSort(NULL, 0);
	}
	
	///
	/// Тества поведението на една сортираща функция
	///
	/// \param [in] pfnSort
	///     Указател към функцията, която ще се тества
	///
	template <typename SAMPLE_TYPE>
	void TestSortingFunction(void pfnSort(SAMPLE_TYPE*, size_t))
	{
		TestSortingFunctionOnSamples<SAMPLE_TYPE>(pfnSort);
		TestSortingFunctionOnNull<SAMPLE_TYPE>(pfnSort);
		TestSortingFunctionOnZeroSize<SAMPLE_TYPE>(pfnSort);
	}


	TEST_CLASS(SortingTest)
	{
	public:
		
		TEST_METHOD(SelectionSort_Test)
		{
			TestSortingFunction(SelectionSort<double>);
		}

		TEST_METHOD(BubbleSort_Test)
		{
			TestSortingFunction(BubbleSort<double>);
		}

		TEST_METHOD(ShakerSort_Test)
		{
			TestSortingFunction(ShakerSort<double>);
		}

		TEST_METHOD(DistributionCounting_Test_Double)
		{
			TestSortingFunction(DistributionCounting<double>);
		}

		TEST_METHOD(DistributionCountingInt_Test_Int)
		{
			TestSortingFunction(DistributionCounting<int>);
		}

		TEST_METHOD(InsertionSort_Test)
		{
			TestSortingFunction(InsertionSort<double>);
		}

		TEST_METHOD(ShellSort_Test)
		{
			TestSortingFunction(ShellSort<double>);
		}

		TEST_METHOD(QuickSort_Test)
		{
			TestSortingFunction(QuickSort<double>);
		}

		TEST_METHOD(HeapSort_Test)
		{
			TestSortingFunction(HeapSort<double>);
		}

		TEST_METHOD(MergeSort_Test)
		{
			TestSortingFunction(MergeSort<double>);
		}

		TEST_METHOD(BottomUpMergeSort_Test)
		{
			TestSortingFunction(BottomUpMergeSort<double>);
		}
	};
}