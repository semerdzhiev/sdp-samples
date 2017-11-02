/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

///
/// Represents one element of a linked list
///
template <class T>
class Box
{
public:
	T Data; /// Data stored within the element
	Box<T>* pNext; /// Pointer to the next element in the chain

public:
	Box(T const & Data, Box<T> *pNext = NULL);
	bool HasSuccessor() const;
};


///
///	Creates a new element and initializes its members
///
template <class T>
Box<T>::Box(T const & Data, Box<T> *pNext)
{
	this->Data = Data;
	this->pNext = pNext;
}


///
///	Checks whether the linked list element has a successor
/// (i.e. points to another element)
///
template <class T>
bool Box<T>::HasSuccessor() const
{
	return this->pNext != NULL;
}