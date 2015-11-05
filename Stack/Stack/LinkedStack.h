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
#include <exception>



///
/// An linked implementation of a FILO stack
///
/// The size of the stack grows and shrinks dynamically
/// depending on the number of stored elements.
///
/// The memory for the elements is allocated on the heap.
///
/// @tparam TYPE
///    Type of the elements stored in the stack
///
template <typename TYPE>
class LinkedStack {
	class Box {
	public:
		TYPE Data;
		Box* pNext;
		Box(TYPE, Box* = NULL);
	};

public:
	LinkedStack();
	~LinkedStack();
	LinkedStack(LinkedStack const & Other);
	LinkedStack& operator=(LinkedStack const & Other);

public:
	void Push(const TYPE & Element);
	bool Pop(TYPE& Element);
	TYPE& Peek();
	void RemoveAll();

	size_t GetSize() const;
	bool IsEmpty() const;

private:
	void Init();
	void Destroy();
	void CopyFrom(LinkedStack const & Other);

private:
	Box* pTop;
	size_t Used;
};


///
/// Constructs a new box for the linked stack
///
template <typename TYPE>
LinkedStack<TYPE>::Box::Box(TYPE Data, Box* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
}



///
/// Constructs an empty stack
///
template <typename TYPE>
LinkedStack<TYPE>::LinkedStack()
{
	Init();
}



///
/// Copy construtor
///
/// @exception std::bad_alloc
///		If the copy operation fails
///
template <typename TYPE>
LinkedStack<TYPE>::LinkedStack(LinkedStack const & Other)
{
	Init();
	CopyFrom(Other); // CopyFrom cleans up all resouces
	                 // if copying fails
}



///
/// Destructor
///
template <typename TYPE>
LinkedStack<TYPE>::~LinkedStack()
{
	Destroy();
}



///
/// Assignment operator
///
/// The operator frees the currently allocated memory first
/// and after that performs the copying.
/// If copying fails, the stack will be left empty.
///
/// @exception std::bad_alloc
///		If the copy operation fails
///
template <typename TYPE>
LinkedStack<TYPE>& LinkedStack<TYPE>::operator=(LinkedStack<TYPE> const & Other)
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
void LinkedStack<TYPE>::Init()
{
	pTop = 0;
	Used = 0;
}



///
/// Empties the stack and frees the allocated memory
///
template <typename TYPE>
void LinkedStack<TYPE>::Destroy()
{
	Box* p;

	while (pTop)
	{
		p = pTop;
		pTop = pTop->pNext;
		delete p;
	}

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
/// @exception std::bad_alloc
///    If the copy operation fails
///
template <typename TYPE>
void LinkedStack<TYPE>::CopyFrom(LinkedStack const& Other)
{
	if (Other.IsEmpty())
		return;

	Box<TYPE> *ours, *theirs;

	// Create a copy of the chain of elements in Other.
	// If copying fails, the function should clean up.
	try
	{
		pTop = new Box(Other.pTop->Data);

		ours = pTop;
		theirs = Other.pTop->pNext;

		while (theirs)
		{
			ours->pNext = new Box(theirs->Data);
			ours = ours->pNext;
			theirs = theirs->pNext;
		}

		Used = Other.Used;
	}
	catch (std::bad_alloc&)
	{
		Destroy();	// OK to call it, because:
					// 1. pTop points to the top of the cloned chain
					// 2. Boxes are allocated in such a manner, so that the
					//    for the last box pNext == NULL
		throw;
	}
}



///
/// Pushes an element on the stack
///
/// @exception std::bad_alloc
///    If memory allocation for a new element fails
///
template <typename TYPE>
void LinkedStack<TYPE>::Push(const TYPE & Element)
{
	pTop = new Box(Element, pTop);

	Used++;
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
bool LinkedStack<TYPE>::Pop(TYPE & Element)
{
	if (Used == 0)
		return false;

	Element = pTop->Data;

	Box* pOld = pTop;
	pTop = pTop->pNext;
	delete pOld;

	Used--;

	return true;
}



///
/// Retrieves the element on the top of the stack
///
/// If the stack is empty, the function asserts.
///
template<typename TYPE>
TYPE& LinkedStack<TYPE>::Peek()
{
	assert(Used != 0);

	return pTop->Data;
}



///
/// Empties the stack
///
/// The function removes all elements and
/// frees the memory allocated for the stack.
///
template <typename TYPE>
void LinkedStack<TYPE>::RemoveAll()
{
	Destroy();
}



///
/// Returns the number of elements currently stored in the stack
///
template<typename TYPE>
size_t LinkedStack<TYPE>::GetSize() const
{
	return Used;
}


///
/// Checks whether the stack is empty
///
template<typename TYPE>
bool LinkedStack<TYPE>::IsEmpty() const
{
	return Used == 0;
}