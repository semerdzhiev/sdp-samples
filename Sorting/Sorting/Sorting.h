#pragma once

template <class T> void swapif(T& a, T& b);
template <class T> void SelectionSort(T* pArr, size_t Size);
template <class T> void BubbleSort(T* pArr, size_t Size);
template <class T> void ShakerSort(T* pArr, size_t Size);
template <class T> int key(T& value);
template <class T> void DistributionCounting(T* pArr, size_t Size);
template <> void DistributionCounting<int>(int* pArr, size_t Size);
template <class T> void InsertionSort(T* pArr, size_t Size);
template <class T> void ShellSortH(T* pArr, size_t Size, size_t k, size_t h);
template <class T> void ShellSort(T* pArr, size_t Size);
template <class T> void QuickSort(T* pArr, size_t Size);
template <class T> size_t Partition(T* pArr, size_t Size);
template <class T> void HeapSort(T* pArr, size_t Size);
template <class T> void Sift(T* pArr, size_t pos, size_t Size);
template <class T> void MergeSort(T* pArr, size_t Size);
template <class T> void MergeSortStep(T* pArr, size_t Size, T* pBuffer);
template <class T> void Merge(T* pA, size_t sizeA, T* pB, size_t sizeB, T* pResult);
template <class T> void BottomUpMergeSort(T* pArr, size_t Size);