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

#include "Box.h"
#include "Iterator.h"

///
/// A single-linked list
///
template <class T>
class LinkedList
{
private:
	Box<T> *pFirst; /// Pointer to the first element in the linked list
	Box<T> *pLast; /// Pointer to the last element in the linked list
	int Size; /// Number of elements in the linked list

public:
	LinkedList();
	LinkedList(LinkedList const &);
	LinkedList& operator= (LinkedList const &);
	~LinkedList();

private:
	void InitializeVariables();
	
public:
	void RemoveAll();
	bool Append(LinkedList const &);

	bool IsEmpty() const;
	int GetCount() const;

	bool AddHead(T const &);
	bool AddTail(T const &);

	void RemoveHead();
	void RemoveTail();
	
	T const & GetHead();
	T const & GetTail();
	
	bool SetHead(T const &);
	bool SetTail(T const &);

	bool InsertAfter(int, T const &);
	bool InsertBefore(int, T const &);
	void RemoveAt(int);
	T const & GetAt(int) const;
	bool SetAt(int, T const &);

	Iterator<T> GetIterator() const;

private:
	Box<T>* FindBoxAt(int) const;
	Box<T>* FindBoxBefore(Box<T>* pBox) const;
	
private:
	static Box<T>* CloneChain(Box<T>* pFirstBox);
	static void DestroyChain(Box<T>* pFirstBox);
	static Box<T>* FindEndOfChain(Box<T>* pFirstBox);
};


///
/// Creates an empty list
///
template <class T>
LinkedList<T>::LinkedList()
{
	InitializeVariables();
}


///
/// Creates a new list and copies in it the contents of another list
///
template <class T>
LinkedList<T>::LinkedList(LinkedList const & list)
{
	InitializeVariables();
	Append(list);
}


///
/// Copies the contents of one list to another
///
template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList const & list)
{
	if(this != &list)
	{
		RemoveAll();
		Append(list);
	}

	return *this;
}


///
/// Destroys a list
///
template <class T>
LinkedList<T>::~LinkedList()
{
	RemoveAll();
}


///
///	Zeros all variables in an object
///	
///	This function is typically used in all constructors to
///	Initialize all member-variables.
///
template <class T>
void LinkedList<T>::InitializeVariables()
{
	this->pFirst = NULL;
	this->pLast = NULL;
	this->Size = 0;
}



///
/// Removes all elements of a list
///
template <class T>
void LinkedList<T>::RemoveAll()
{
	DestroyChain(this->pFirst);

	InitializeVariables();
}


///
/// Copies and appends the contents of another list to this one
///
/// \return
///		true if the function succeeds in copying the data.
///		If it fails, the list remains unchanged and
///		the function returns false.
///
template <class T>
bool LinkedList<T>::Append(LinkedList const & list)
{
	// If there is nothing to copy, don't copy :-)
	if(list.IsEmpty())
	{
		return true;
	}
	else
	{
		// Try to clone the data from the other list
		Box<T> *pNewChain = CloneChain(list.pFirst);

		if(pNewChain)
		{
			this->pLast->pNext = pNewChain;
			this->pLast = FindEndOfChain(pNewChain);
		}

		return pNewChain != NULL;
	}
}


///
/// Checks whether a list is empty or not
///
template <class T>
bool LinkedList<T>::IsEmpty() const
{
	return this->Size == 0;
}


///
/// Returns how many elements are stored in the list
///
template <class T>
int LinkedList<T>::GetCount() const
{
	return this->Size;
}


///
/// Prepends a new element at the start of a list
///
/// \return
///		true if the function succeeds in adding the element.
///		Otherwise the list remains unchanged and the
///		function returns false.
///
template <class T>
bool LinkedList<T>::AddHead(T const & data)
{
	Box<T> *pNewBox = new Box<T>(data, this->pFirst);

	if(pNewBox)
	{
		if(this->IsEmpty())
		{
			this->pLast = pNewBox;
		}

		this->pFirst = pNewBox;

		// Increment the size of the list
		this->Size++;
	}

	return pNewBox != NULL;
}


///
/// Appends a new element at the end of a list
///
/// \return
///		true if the function succeeds in adding the element.
///		Otherwise the list remains unchanged and the
///		function returns false.
///
template <class T>
bool LinkedList<T>::AddTail(T const & data)
{
	Box<T> *pNewBox = new Box<T>(data);

	if(pNewBox)
	{
		if(this->IsEmpty())
		{
			this->pFirst = pNewBox;
			this->pLast = pNewBox;
		}
		else
		{
			this->pLast->pNext = pNewBox;
			this->pLast = pNewBox;
		}

		// Increment the size of the list
		this->Size++;
	}

	return pNewBox != NULL;
}


///
/// Removes the first element of a list
///
///	If the list has no elements, the function does nothing
///
template <class T>
void LinkedList<T>::RemoveHead()
{
	// We can only remove the head of a non-empty list
	if( ! this->IsEmpty() )
	{
		assert(this->pFirst != NULL);

		// This pointer will keep the address of the old first box.
		Box<T> *pOldHead = this->pFirst;

		// Advance the first element pointer with one position forward
		this->pFirst = this->pFirst->pNext;

		// If this was the last element, the list is now empty and we have
		// to set the last element pointer to NULL
		if(this->pFirst == NULL)
		{
			this->pLast = NULL;
		}

		// Decrement the list size
		this->Size--;

		// Erase the old first element
		delete pOldHead;
	}
}


///
/// Removes the last element of a list
///
///	If the list has no elements, the function does nothing
///
template <class T>
void LinkedList<T>::RemoveTail()
{
	if( ! this->IsEmpty() )
	{
		RemoveAt(this->Size - 1);
	}
}


///
///	Returns the first element in the list
///
template <class T>
T const & LinkedList<T>::GetHead()
{
	assert( ! this->IsEmpty() );

	return this->pFirst->Data;
}


///
///	Returns the last element in the list
///
template <class T>
T const & LinkedList<T>::GetTail()
{
	assert( ! this->IsEmpty() );

	return this->pLast->Data;
}


///
///	Changes the value of the first element in the list
///
template <class T>
bool LinkedList<T>::SetHead(T const & value)
{
	if( ! this->IsEmpty() )
	{
		this->pFirst->Data = value;
		return true;
	}
	else
	{
		return false;
	}
}


///
///	Changes the value of the last element in the list
///
template <class T>
bool LinkedList<T>::SetTail(T const & value)
{
	if( ! this->IsEmpty() )
	{
		this->pLast->Data = value;
		return true;
	}
	else
	{
		return false;
	}
}


///
///	Insert an element after a specific index in the list
///
template <class T>
bool LinkedList<T>::InsertAfter(int Index, T const & Value)
{
	// Try to find the box at the specified index
	Box<T> *pBoxAtIndex = FindBoxAt(Index);

	// If there is such box, try to insert an element after it
	if(pBoxAtIndex)
	{
		Box<T> *pNewBox = new Box<T>(Value, pBoxAtIndex->pNext);

		// If memory allocation fails, return false.
		if ( ! pNewBox)
		{
			return false;
		}

		// Make the box at the desired index point to the new box
		pBoxAtIndex->pNext = pNewBox;

		// If the element is being inserted just at the end of the list,
		// update the last element pointer.
		if(pBoxAtIndex == this->pLast)
		{
			this->pLast = pNewBox;
		}

		// Increment the size
		this->Size++;
		
		return true;
	}
	else
	{
		return false;
	}
}


///
///	Insert an element before a specific index in the list
///
template <class T>
bool LinkedList<T>::InsertBefore(int Index, T const & Value)
{
	// Trying to add before index 0 is the same as adding a new head
	if(Index == 0)
	{
		return AddHead(Value);
	}

	// Otherwise we can solve the task by inserting the value
	// after (Index - 1)
	else
	{
		return InsertAfter(Index - 1, Value);
	}
}


///
///	Removes the element at a specific index in the list
///
template <class T>
void LinkedList<T>::RemoveAt(int Index)
{
	// Trying to remove the first element is equivalent to a call to RemoveHead()
	// Also here we handle the case when there is only one element in the list.
	if(Index == 0)
	{
		this->RemoveHead();
	}

	// Here we should have that:
	// (1) There are at least two elements in the list
	// (2) Index != 0
	// (3) We are not trying to remove the first element
	else
	{
		assert(this->GetCount() >= 2);
					
		// Find the box before the one we want to remove
		Box<T> *pBoxBeforeIndex = FindBoxAt(Index - 1);

		// Make sure the Index is valid!
		assert(pBoxBeforeIndex != NULL);

		// Get a pointer to the box that we want to remove
		Box<T> *pBoxAtIndex = pBoxBeforeIndex->pNext;

		// If the box that we want to remove is the last one,
		// update the last element pointer accordingly
		if(Index == this->Size - 1)
		{
			this->pLast = pBoxBeforeIndex;
		}

		// Fix the next pointer of the previous box.
		pBoxBeforeIndex->pNext = pBoxAtIndex->pNext;

		// Delete the box
		delete pBoxAtIndex;

		// Decrement the size
		this->Size--;
	}	
}


///
///	Returns the value of the element at a specific index in the list
///
template <class T>
T const & LinkedList<T>::GetAt(int Index) const
{
	Box<T> *pBox = FindBoxAt(Index);

	assert(pBox != NULL);

	return pBox->Data;
}


///
///	Sets the value of the element at a specific index in the list
///
template <class T>
bool LinkedList<T>::SetAt(int Index, T const & Value)
{
	Box<T> *pBox = FindBoxAt(Index);

	if(pBox != NULL)
	{
		pBox->Data = Value;
	}

	return pBox != NULL;
}


///
/// Finds the box at a specific index in the list
///
/// \return
///		NULL if there is no such index in the list
///
template <class T>
Box<T>* LinkedList<T>::FindBoxAt(int Index) const
{
	if(Index < 0 || Index >= this->Size)
	{
		return NULL;
	}
	else
	{
		Box<T> *p = this->pFirst;

		for(int i = 0; i < Index; i++)
		{
			p = p->pNext;
		}

		return p;
	}
}


///
/// Searches for a box in the list, which points to another box
///
/// \return
///		The address of the box we are looking for or
///		NULL if there is no such box in the list.
///
template <class T>
Box<T>* LinkedList<T>::FindBoxBefore(Box<T>* pBox) const
{
	Box<T> *pCurrent = this->pFirst;

	while(pCurrent && pCurrent->pNext != pBox)
	{
		pCurrent = pCurrent->pNext;
	}

	// At this point, if we have reached the end of the list
	// without finding the desired box, pCurrent is NULL.
	// Otherwise it points to the box we are looking for.
	return pCurrent;
}


///
///	Return a new iterator for this list
///
template <class T>
Iterator<T> LinkedList<T>::GetIterator() const
{
	return Iterator<T>(this->pFirst);
}


//----------------------------------------------------------------------
// OPERATIONS ON CHAINS

///
///	Clones a chain of boxes
///
///	The function receives a pointer to the first box
///	in a chain of boxes and creates a new, identical chain.
///
///	If the function fails it returns NULL.
///	Otherwise it returns a pointer to the first box
///	of the new chain.
///
template <class T>
Box<T>* LinkedList<T>::CloneChain(Box<T>* pFirstBox)
{
	if(pFirstBox)
	{
		// Pointer to the start of the new chain
		Box<T>* pNewChain = new Box(pFirstBox);

		// Pointer to the element that we have to copy next
		Box<T>* pReadFrom = pFirstBox->pNext;

		// Pointer to the element after which we have to copy the new element
		Box<T>* pWriteAfter = pNewChain;

		while(pReadFrom)
		{
			if( ! pWriteAfter)
			{
				DestroyChain(pNewChain);
				pNewChain = NULL;
				break;
			}

			pWriteAfter->pNext = new Box(pReadFrom);
			pWriteAfter = pWriteAfter->pNext;

			pReadFrom = pReadFrom->pNext;
		}

		return pNewChain;
	}

	return NULL;	
}


///
///	Destroys all boxes in a chain
///
///	\param [in] pFirstBox
///		A pointer to the first box in the chain.
///
template <class T>
void LinkedList<T>::DestroyChain(Box<T>* pFirstBox)
{
	Box<T>* pCurrent = pFirstBox;
	Box<T>* pOld = pFirstBox;
	
	while(pCurrent)
	{
		pOld = pCurrent;
		pCurrent = pCurrent->pNext;
		delete pOld;
	}
}


///
///	Returns a pointer to the last box in a chain
///
template <class T>
Box<T>* LinkedList<T>::FindEndOfChain(Box<T>* pFirstBox)
{
	Box<T>* pCurrent = pFirstBox;

	if(pCurrent)
	{
		while(pCurrent->pNext)
		{
			pCurrent = pCurrent->pNext;
		}
	}
	
	return pCurrent;
}