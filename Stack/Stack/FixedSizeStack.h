/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <assert.h>



///
/// An implementation of a FILO stack
///
/// The maximum size of the stack is fixed
/// and cannot be changed.
///
/// The memory for the elements is allocated on the heap.
///
/// @tparam TYPE
///    Type of the elements stored in the stack
///
template <typename TYPE>
class FixedSizeStack {
public:
	FixedSizeStack(size_t Size);
	~FixedSizeStack();
	FixedSizeStack(FixedSizeStack const & Other);
	FixedSizeStack& operator=(FixedSizeStack const & Other);

public:
	void Push(const TYPE & Element);
	bool Pop(TYPE& Element);
	TYPE& Peek();
	void RemoveAll();

	size_t GetSize() const;
	size_t GetMaxSize() const;
	bool IsEmpty() const;

private:
	void Init();
	void Destroy();
	void CopyFrom(FixedSizeStack const & Other);

private:
	TYPE* pData;
	size_t Allocated;
	size_t Used;
};


///
/// Constructs an empty stack
///
template <typename TYPE>
FixedSizeStack<TYPE>::FixedSizeStack(size_t Size)
{
	Init();
	pData = new TYPE[Size];
	Allocated = Size;
}



///
/// Copy constructor
///
template <typename TYPE>
FixedSizeStack<TYPE>::FixedSizeStack(FixedSizeStack const & Other)
{
	Init();
	CopyFrom(Other);
}



///
/// Destroys a stack
///
template <typename TYPE>
FixedSizeStack<TYPE>::~FixedSizeStack()
{
	Destroy();
}



///
/// Assignment operator
///
template <typename TYPE>
FixedSizeStack<TYPE>& FixedSizeStack<TYPE>::operator=(FixedSizeStack<TYPE> const & Other)
{
	if (this != &Other)
	{
		Destroy();
		CopyFrom(Other);
	}

	return *this;
}



///
/// Assigns initial values for the data-members of the object
///
/// The values are proper for an empty stack for which no memory
/// is allocated. e.g. on construction or after freeing the memory.
///
template <typename TYPE>
void FixedSizeStack<TYPE>::Init()
{
	pData = NULL;
	Allocated = 0;
	Used = 0;
}



///
/// Empties the stack and frees the allocated memory
///
template <typename TYPE>
void FixedSizeStack<TYPE>::Destroy()
{
	delete[] pData;
	Init();
}



///
/// Makes the current object a copy of another one
///
/// The function assumes that the object is empty
/// (i.e. no memory is allocated for it)
///
/// @param [in] Other
///    Object to copy from. Can be either empty or non-empty
///
template <typename TYPE>
void FixedSizeStack<TYPE>::CopyFrom(FixedSizeStack<TYPE> const& Other)
{
	if (Other.IsEmpty())
		return;

	pData = new TYPE[Other.Allocated];
	Allocated = Other.Allocated;
	Used = Other.Used;

	for (size_t i = 0; i < Used; i++)
		pData[i] = Other.pData[i];
}



///
/// Pushes an element on the stack
///
/// If the stack is full, the function asserts
///
template <typename TYPE>
void FixedSizeStack<TYPE>::Push(const TYPE & Element)
{
	assert(Used < Allocated);

	pData[Used++] = Element;
}



///
/// Removes and returns the element on top of the stack
///
/// @param [out] Element
///    A parameter, which will receive the value of the top element.
///    If the stack is empty, this element will not be altered.
///
/// @return
///    true if the operation was successful or
///    false if the stack was empty.
///
template<typename TYPE>
bool FixedSizeStack<TYPE>::Pop(TYPE & Element)
{
	if (Used > 0)
	{
		Element = pData[--Used];
		return true;
	}

	return false;
}


///
/// Retrieves the element on the top of the stack
///
/// If the stack is empty, the function asserts.
///
template<typename TYPE>
TYPE& FixedSizeStack<TYPE>::Peek()
{
	assert(Used > 0);

	return pData[Used - 1];
}



///
/// Empties the stack
///
/// The function removes all elements, but does not
/// free the memory allocated for the stack.
///
template <typename TYPE>
void FixedSizeStack<TYPE>::RemoveAll()
{
	Used = 0;
}



///
/// Returns the number of elements currently stored in the stack
///
template<typename TYPE>
size_t FixedSizeStack<TYPE>::GetSize() const
{
	return Used;
}



///
/// Returns the maximum number of elements
/// that can be stored in the stack
///
template<typename TYPE>
size_t FixedSizeStack<TYPE>::GetMaxSize() const
{
	return Allocated;
}



///
/// Checks whether the stack is empty
///
template<typename TYPE>
bool FixedSizeStack<TYPE>::IsEmpty() const
{
	return Used == 0;
}