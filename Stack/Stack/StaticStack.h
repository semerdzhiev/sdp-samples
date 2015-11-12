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
/// The memory for the elements is allocated on the stack.
///
/// @tparam TYPE
///    Type of the elements stored in the stack
///
/// @tparam MAX_SIZE
///    Maximum number of elements that can be stored
///    in the stack
///
template <typename TYPE, int MAX_SIZE>
class StaticStack {
public:
	StaticStack();

public:
	void Push(const TYPE & Element);
	bool Pop(TYPE& Element);
	TYPE& Peek();
	void RemoveAll();

	size_t GetSize() const;
	size_t GetMaxSize() const;
	bool IsEmpty() const;

private:
	TYPE Data[MAX_SIZE];
	size_t Size;
};



///
/// Constructs an empty stack
///
template<typename TYPE, int MAX_SIZE>
inline StaticStack<TYPE, MAX_SIZE>::StaticStack()
{
	Size = 0;
}


///
/// Pushes an element on the stack
///
/// If the stack is full, the function asserts
///
template<typename TYPE, int MAX_SIZE>
void StaticStack<TYPE, MAX_SIZE>::Push(const TYPE & Element)
{
	assert(Size < MAX_SIZE);

	Data[Size++] = Element;
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
template<typename TYPE, int MAX_SIZE>
bool StaticStack<TYPE, MAX_SIZE>::Pop(TYPE & Element)
{
	if (Size > 0)
	{
		Element = Data[--Size];
		return true;
	}

	return false;
}



///
/// Retrieves the element on the top of the stack
///
/// If the stack is empty, the function asserts.
///
template<typename TYPE, int MAX_SIZE>
TYPE& StaticStack<TYPE, MAX_SIZE>::Peek()
{
	assert(Size > 0);

	return Data[Size - 1];
}



///
/// Empties the stack
///
/// The function removes all elements, but does not
/// free the memory allocated for the stack.
///
template<typename TYPE, int MAX_SIZE>
inline void StaticStack<TYPE, MAX_SIZE>::RemoveAll()
{
	Size = 0;
}



///
/// Returns the number of elements currently stored in the stack
///
template<typename TYPE, int MAX_SIZE>
inline size_t StaticStack<TYPE, MAX_SIZE>::GetSize() const
{
	return Size;
}



///
/// Returns the maximum number of elements
/// that can be stored in the stack
///
template<typename TYPE, int MAX_SIZE>
inline size_t StaticStack<TYPE, MAX_SIZE>::GetMaxSize() const
{
	return MAX_SIZE;
}



///
/// Checks whether the stack is empty
///
template<typename TYPE, int MAX_SIZE>
inline bool StaticStack<TYPE, MAX_SIZE>::IsEmpty() const
{
	return Size == 0;
}
