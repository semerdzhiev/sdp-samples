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
private:
    
	int *pData;           /// Pointer to the array's contents
	size_t BufferSize; /// Size of the allocated buffer
	size_t Size; /// Number of elements currently stored in the array

public:
	DynamicArray();
	DynamicArray(DynamicArray const &);
	DynamicArray& operator=(DynamicArray const &);
	~DynamicArray();

public:
	void Clear();
	
	void PushBack(int Element);

    void Reserve(size_t Size);

	size_t GetBufferSize() const;
	size_t GetSize() const;
	
	int GetAt(size_t) const;
	void SetAt(size_t, int);

	void Print() const;

public:
    DynamicArray& operator+=(DynamicArray const &);
    DynamicArray operator+(DynamicArray const &) const;
	DynamicArrayElementProxy operator[](size_t);
	const DynamicArrayElementProxy operator[](size_t) const;

private:
	void CopyFrom(DynamicArray const &);
	void Resize(size_t NewBufferSize);
    size_t CalculateGrowth(size_t NewSize);
};


///
/// Represents one element in the dynamic array
///
class DynamicArrayElementProxy
{
private:
    /// Pointer to the dynamic array that created the proxy object
    DynamicArray *pParent;     

    /// Index of the element represented by the proxy
    size_t ParentElementIndex; 
	
public:
	DynamicArrayElementProxy(DynamicArray *, size_t);
	DynamicArrayElementProxy& operator=(int);
    operator int() const;
};