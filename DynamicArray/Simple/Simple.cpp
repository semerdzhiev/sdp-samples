/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <algorithm>
#include <ctime>


///
/// Represents a dynamic array
///
struct DynamicArray
{    
    int *pData;        /// Pointer to the array's contents
    size_t BufferSize; /// Size of the allocated buffer
    size_t Size;       /// Number of elements currently stored in the array
};


///
/// Initializes a newly created dynamic array
///
void Init(DynamicArray* pArr)
{
    pArr->pData = nullptr;
    pArr->BufferSize = 0;
    pArr->Size = 0;
}


///
/// Empties a dynamic array and frees all allocated resources
///
void Free(DynamicArray* pArr)
{
    delete[] pArr->pData;

    Init(pArr); // zero all members of the structure
}


///
/// Changes the size of a dynamic array's buffer to NewBufferSize
///
/// \param NewBufferSize
///    Specifies the desired new size of the buffer.
///    If it is the same as the current buffer size, no operations will be performed.
///    If it is zero, the array will be emptied.
///    If it is less than the number of currently stored elements,
///    all excessive elements will be lost.
///
void Resize(DynamicArray* pArr, size_t NewBufferSize)
{
    if (NewBufferSize == pArr->BufferSize)
        return;

    int *pTemp = 0;
    size_t elementsToCopy = std::min(NewBufferSize, pArr->Size);

    if (NewBufferSize != 0)
    {
        pTemp = new int[NewBufferSize];

        for (size_t i = 0; i < elementsToCopy; ++i)
            pTemp[i] = pArr->pData[i];
    }

    delete [] pArr->pData;
    pArr->pData = pTemp;
    pArr->BufferSize = NewBufferSize;
    pArr->Size = elementsToCopy;
}


inline size_t NextSize(size_t s)
{
    return s == 0 ? 1 : s * 2;
}


///
/// Append a new element to the end of the array
///
void PushBack(DynamicArray* pArr, int Element)
{
    if (pArr->Size >= pArr->BufferSize)
        Resize(pArr, NextSize(pArr->BufferSize));

    pArr->pData[pArr->Size++] = Element;
}


void PrintArrayInfo(DynamicArray* pArr)
{
    std::cout
        << "Array at 0x"   << pArr
        << " buffer at 0x" << pArr->pData
        << " size ("       << pArr->Size
        << " / "           << pArr->BufferSize
        << ")\n";
}


int main()
{
    DynamicArray da;
    Init(&da);

    for(int i = 0; i < 35; i++)
    {
        PushBack(&da, i);
        PrintArrayInfo(&da);
    }    

    Free(&da);

    return 0;
}
