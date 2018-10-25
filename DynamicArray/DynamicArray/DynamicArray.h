/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

class DynamicArrayElementProxy;

///
/// Represents a dynamic array
///
class DynamicArray
{
public:
	///
	/// Represents one element in the dynamic array
	///
	class ElementProxy
	{
	private:
		DynamicArray * pArray; /// Pointer to the dynamic array that created the proxy object
		size_t ElementIndex;   /// Index of the element represented by the proxy

	public:
		ElementProxy(DynamicArray *, size_t);
		ElementProxy& operator=(int);
		operator int() const;
	};


	class Iterator {
	private:
		DynamicArray * pArray;
		size_t Index; /// Current position of the iterator in the array
	public:
		Iterator(DynamicArray *pArray);
		int GetCurrent() const;
		void SetCurrent(int);
		void MoveNext();
		void Rewind();
		bool EndReached() const;
	};


private:
	int *pData;        /// Pointer to the array's contents
	size_t BufferSize; /// Size of the allocated buffer
	size_t Size;       /// Number of elements currently stored in the array

public:
	DynamicArray();
	DynamicArray(DynamicArray const &);
	DynamicArray& operator=(DynamicArray const &);
	~DynamicArray();

public:
	void Clear();

	void PushBack(int Element);
	void PopBack();

    void Reserve(size_t Size);

	size_t GetBufferSize() const;
	size_t GetSize() const;
	
	int GetAt(size_t) const;
	void SetAt(size_t, int);

	Iterator GetIterator();

	void Print() const;

public:
    DynamicArray& operator+=(DynamicArray const &);
    DynamicArray operator+(DynamicArray const &) const;
	ElementProxy operator[](size_t);
	const ElementProxy operator[](size_t) const;

private:
	void CopyFrom(DynamicArray const &);
	void Resize(size_t NewBufferSize);
    size_t CalculateGrowth(size_t NewSize);
};


