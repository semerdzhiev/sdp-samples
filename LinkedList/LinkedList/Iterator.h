/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "Box.h"

template <class T>
class Iterator
{
private:
	Box<T> *pStart;
	Box<T> *pCurrent;
public:
	Iterator(Box<T> *pStart);

	T const & GetCurrent() const;
	void SetCurrent(T const &);
	void MoveNext();
	void Rewind();
	bool EndReached() const;
};


///
///	Creates a new interator and initializes it, so that
/// it will start from the element pStart points to.
///
template <class T>
Iterator<T>::Iterator(Box<T> *pStart)
{
	this->pStart = this->pCurrent = pStart;
}


///
///	Retrieves the current list element
///
template <class T>
T const & Iterator<T>::GetCurrent() const
{
	assert( ! this->EndReached() );

	return this->pCurrent->Data;
}


///
///	Changes the value of the current list element
///
template <class T>
void Iterator<T>::SetCurrent(T const & Value)
{
	assert( ! this->EndReached() );

	this->pCurrent->Data = Value;
}


///
///	Moves the iterator one step forward
///
///	If the iterator has reached the end of the list,
/// the function does nothing.
///
template <class T>
void Iterator<T>::MoveNext()
{
	if(this->pCurrent)
	{
		this->pCurrent = this->pCurrent->pNext;
	}
}


///
///	Returns the iterator to its initial state
///
template <class T>
void Iterator<T>::Rewind()
{
	this->pCurrent = this->pStart;
}


///
///	Checks whether the iterator has moved past the end of the list.
///
///	\return	
///     true if there are no more elements to be iterated,
///     or false otherwise.
///
template <class T>
bool Iterator<T>::EndReached() const
{
	return this->pCurrent == NULL;
}