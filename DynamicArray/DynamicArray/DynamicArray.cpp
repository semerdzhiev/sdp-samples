﻿/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <algorithm>

#include <vector>

#include "DynamicArray.h"

///
/// Initializes an empty array
///
DynamicArray::DynamicArray()
{
	pData = NULL;
	BufferSize = 0;
	Size = 0;
}


///
/// Copy constructor
///
DynamicArray::DynamicArray(DynamicArray const & other)
{
	CopyFrom(other);
}


///
/// Assignment operator
///
DynamicArray& DynamicArray::operator=(DynamicArray const & other)
{
	if(this != &other)
	{
		Clear();
		CopyFrom(other);
	}

	return *this;
}


///
/// Destructor
///
DynamicArray::~DynamicArray()
{
	Clear();
}



///
/// Empties the dynamic array and frees all allocated resources
///
void DynamicArray::Clear()
{
	delete [] pData;

	pData = NULL;
	BufferSize = 0;
	Size = 0;
}



///
/// Append a new element to the end of the array
///
void DynamicArray::PushBack(int Element)
{
    if (Size >= BufferSize)
        Resize(CalculateGrowth(Size + 1));

    pData[Size++] = Element;
}



///
/// Ensure that the dynamic array will be able
/// to store at least Size elements without
/// performing reallocations.
///
void DynamicArray::Reserve(size_t Size)
{
    Resize(CalculateGrowth(Size));
}



///
/// Returns the size of the allocated buffer
///
size_t DynamicArray::GetBufferSize() const
{
    return BufferSize;
}



///
/// Returns the number of elements stored in the array
///
size_t DynamicArray::GetSize() const
{
    return Size;
}


///
/// Returns the element at a given index
///
/// \exception std::out_of_range
///     The index is out of the range
///
int DynamicArray::GetAt(size_t index) const
{
    if (index >= Size)
        throw std::out_of_range("Index out of range!");

    return pData[index];
}


///
/// Modifies the element at a given index
///
/// \exception std::out_of_range
///     The index is out of the range
///
void DynamicArray::SetAt(size_t index, int value)
{
    if (index >= Size)
        throw std::out_of_range("Index out of range!");

    pData[index] = value;
}



///
/// Prints array information to STDOUT
///
void DynamicArray::Print() const
{
    std::cout
        << "Dynamic Array at 0x" << this
        << ", buffer at 0x" << pData
        << ", size (" << Size
        << " / " << BufferSize
        << ")\n";

    if (Size > 0)
    {
        std::cout << "Contents: " << pData[0];

        for (size_t i = 1; i < Size; i++)
            std::cout << ", " << pData[i];

        std::cout << "\n";
    }
}



///
/// Copies the contents of another object into this one
///
/// The function assumes that the current object is empty.
/// It does not perform any actions to free resources.
/// If necessary, call Clear() before CopyFrom().
///
void DynamicArray::CopyFrom(DynamicArray const & other)
{
    pData = new int[other.BufferSize];

    for (size_t i = 0; i < other.Size; i++)
        pData[i] = other.pData[i];

    BufferSize = other.BufferSize;
    Size = other.Size;
}



///
/// Changes the size of the dynamic array's buffer to NewBufferSize
///
/// \param NewBufferSize
///    Specifies the desired new size of the buffer.
///    If it is the same as the current buffer size, no operations will be performed.
///    If it is zero, the array will be emptied.
///    If it is less than the number of currently stored elements,
///    all excessive elements will be lost.
///
void DynamicArray::Resize(size_t NewBufferSize)
{
    if (NewBufferSize == BufferSize)
        return;

    int *pTemp = 0;
    size_t elementsToCopy = std::min(NewBufferSize, Size);

	
    if (NewBufferSize != 0)
    {
        pTemp = new int[NewBufferSize];

        for (size_t i = 0; i < elementsToCopy; ++i)
            pTemp[i] = pData[i];
    }

	delete [] pData;
	pData = pTemp;
	BufferSize = NewBufferSize;
	Size = elementsToCopy;
}



///
/// Determines how much to grow the array by,
/// in order to be able to contain NewSize elements
///
size_t DynamicArray::CalculateGrowth(size_t NewSize)
{
    if (NewSize < BufferSize)
        return BufferSize; // already at sufficient size

    size_t Geometric = BufferSize * 2;

    return Geometric < NewSize ? NewSize : Geometric;
}



///
/// Appends the contents of another array to this one
///
DynamicArray& DynamicArray::operator+=(DynamicArray const& rhs)
{
    Reserve(Size + rhs.Size);

    for (size_t i = 0; i < rhs.Size; ++i)
        PushBack(rhs.pData[i]);

    return *this;
}



///
/// Generates a new arraym which is a concatenation of this one and rhs
///
DynamicArray DynamicArray::operator+ (DynamicArray const& rhs) const
{
	DynamicArray temp;
    temp.Reserve(Size + rhs.Size);
    temp += *this;
    temp += rhs;
    return temp;
}



///
/// Returns a proxy object, which represents the element at a given index
///
/// This version of the operator is used for non-constant arrays.
/// It returns a proxy object, which can be used to modify the array's elements
///
/// \remark
///    The operator does not check whether index falls within the bounds of the array.
///    Such a check is being performed by the proxy object, every time it is used.
///
/// \remark
///    The proxy object is linked to a specific index and not to a specific element.
///    Even if the underlying buffer is reallocated at a different addres,
///    the proxy object will continue to point to the element at the given index.
///
DynamicArrayElementProxy DynamicArray::operator[](size_t index)
{
	return DynamicArrayElementProxy(this, index);
}


///
/// Returns a proxy object, which represents the element at a given index
///
/// This version of the operator is used for constant arrays.
/// It returns a proxy object, which *cannot* be used to modify the array's elements
///
/// For additional information check the remarks to the non-constant
/// version of the subscript operator
///
const DynamicArrayElementProxy DynamicArray::operator[](size_t index) const
{
	// We need a const_cast, because the proxy's constructor
	// will only accept a non-constant object
	return DynamicArrayElementProxy(const_cast<DynamicArray*>(this), index);
}



/// ============================================================================



///
/// Constructs a proxy object, which represents the element
/// at position ElementIndex in the dynamic array pointed to by pParent
///
DynamicArrayElementProxy::DynamicArrayElementProxy(DynamicArray * pDynamicArray, size_t ElementIndex) :
	pParent(pDynamicArray),
	ParentElementIndex(ElementIndex)
{
}


///
/// Returns the element's value
///
DynamicArrayElementProxy::operator int() const
{
	return pParent->GetAt(ParentElementIndex);
}


///
/// Modifies the element's value
///
DynamicArrayElementProxy& DynamicArrayElementProxy::operator=(int value)
{
	pParent->SetAt(ParentElementIndex, value);

	return *this;
}
