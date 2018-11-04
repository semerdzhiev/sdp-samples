/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <assert.h>

///
/// A single-linked list
///
template <class T>
class LinkedList {
public:
    ///
    /// Represents one box in a linked list
    ///
    class Box {
    public:
        T Data;     /// Data stored within the element
        Box* pNext; /// Pointer to the next element in the chain

    public:
        Box(const T & Data, Box *pNext = nullptr)
            : Data(Data), pNext(pNext)
        {
        }

        bool HasSuccessor() const
        {
            return pNext != nullptr;
        }
    };



    class Iterator {
    private:
        Box *pStart;   /// Pointer to the first box in the linked list
        Box *pCurrent; /// Current position of the iterator
    
    public:
        Iterator(Box *pStart)
            : pStart(pStart), pCurrent(pStart)
        {
        }

        ///
        /// Retrieves the value of the current element
        ///
        T const & GetCurrent() const
        {
            return pCurrent->Data;
        }

        ///
        /// Changes the value of the current element
        ///
        void SetCurrent(T const & Value)
        {
            pCurrent->Data = Value;
        }

        ///
        /// Moves the iterator one step forward
        ///
        /// If the iterator has reached the end of the list,
        /// the function does nothing.
        ///
        void MoveNext()
        {
            if(pCurrent)
                pCurrent = pCurrent->pNext;
        }

        ///
        /// Returns the iterator to its initial state
        ///
        void Rewind()
        {
            pCurrent = pStart;
        }

        ///
        /// Checks whether the iterator has moved past the end of the list.
        ///
        /// \return    
        ///    true if there are no more elements to be iterated,
        ///    or false otherwise.
        ///
        bool EndReached() const
        {
            return pCurrent == nullptr;
        }
    };

    
private:
    Box *pFirst; /// Pointer to the first box in the linked list
    Box *pLast;  /// Pointer to the last box in the linked list
    size_t Size;    /// Number of elements in the linked list


public:
    ///
    /// Creates an empty list
    ///
    LinkedList()
    {
        ZeroVariables();
    }

    ///
    /// Creates a new list and copies in it the contents of another list
    ///
    LinkedList(LinkedList const & Other)
    {
        ZeroVariables();
        Append(Other);
    }
    
    ///
    /// Copies the contents of one list to another
    ///
    LinkedList& operator= (const LinkedList & Other)
    {
        if (this != &Other)
        {
            Clear();
            Append(Other);
        }

        return *this;
    }

    ///
    /// Destroys a list
    ///
    ~LinkedList()
    {
        Clear();
    }

private:
    void ZeroVariables()
    {
        pFirst = nullptr;
        pLast = nullptr;
        Size = 0;
    }
    
public:
    ///
    /// Checks whether the list is empty or not
    ///
    bool IsEmpty() const
    {
        return Size == 0;
    }

    ///
    /// Returns the number of elements in the list
    ///
    size_t GetSize() const
    {
        return Size;
    }

    ///
    /// Removes all elements of a list
    ///
    void Clear()
    {
        DestroyChain(pFirst);
        ZeroVariables();
    }

    ///
    /// Copies and appends the contents of another list to this one
    ///
    /// \return
    ///    true if the function succeeds in copying the data.
    ///    If it fails, the list remains unchanged and
    ///    the function returns false.
    ///
    bool Append(LinkedList const & Other)
    {
        // If there is nothing to copy, don't copy :-)
        if (Other.IsEmpty())
            return true;

        // Try to clone the data from the other list
        Box *pNewChainStart, *pNewChainEnd;
        CloneChain(Other.pFirst, pNewChainStart, pNewChainEnd);

        if (!pNewChainStart)
            return false;

        if (Size == 0)
            pFirst = pNewChainStart;
        else
            pLast->pNext = pNewChainStart;

        pLast = pNewChainEnd;            

        Size += Other.Size;

        return pNewChainStart != nullptr;
    }


    ///
    /// Prepends a new element at the start of the list
    ///
    /// \exception std::bad_alloc If memory allocation fails
    ///
    void PushFront(const T & Value)
    {
        Box *pNewBox = new Box(Value, pFirst);

        if (IsEmpty())
            pLast = pNewBox;

        pFirst = pNewBox;
        ++Size;
    }


    ///
    /// Appends a new element at the end of a list
    ///
    /// \exception std::bad_alloc If memory allocation fails
    ///
    void PushBack(T const & Value)
    {
        Box *pNewBox = new Box(Value);

        if (IsEmpty())
        {
            pFirst = pLast = pNewBox;
        }
        else
        {
            this->pLast->pNext = pNewBox;
            this->pLast = pNewBox;
        }

        ++Size;
    }


    ///
    /// Removes the first element of a list
    ///
    /// If the list has no elements, the function does nothing
    ///
    void PopFront()
    {
        if (IsEmpty())
            return; // We can only remove the head of a non-empty list

        // This pointer will keep the address of the old first box.
        Box *pOldHead = pFirst;

        // Advance the first element pointer with one position forward
        pFirst = pFirst->pNext;

        // If this was the last element, the list is now empty and we have
        // to set the last element pointer to NULL
        if (pFirst == nullptr)
            pLast = nullptr;

        // Decrement the list size
        --Size;

        // Destroy the old first element
        delete pOldHead;
    }


    ///
    /// Removes the last element of a list
    ///
    /// If the list has no elements, the function does nothing
    ///
    void PopBack()
    {
        if ( ! IsEmpty())
            RemoveAt(Size - 1);
    }

    
    ///
    /// Return the first element of the list
    ///
    /// \exception std::exception If the list is empty
    ///
    T& Front()
    {
        if (Size == 0)
            throw std::exception();
        
        return pFirst->Data;
    }

    const T& Front() const
    {
        return const_cast<LinkedList<T>*>(this)->Front();
    }

    ///
    /// Return the last element of the list
    ///
    /// \exception std::exception If the list is empty
    ///
    T& Back()
    {
        if (Size == 0)
            throw std::exception();

        return pLast->Data;
    }

    const T& Back() const
    {
        return const_cast<LinkedList<T>*>(this)->Back();
    }

    ///
    /// Returns the element at the specified index in the list
    ///
    /// \exception std::out_of_range If the specified index is invalid
    ///
    T & At(size_t Index)
    {
        if (Index >= Size)
            throw std::out_of_range("Index exceeds the number of elements in the list");

        return FindBoxAt(Index)->Data;
    }

    const T & At(size_t Index) const
    {
        if (Index >= Size)
            throw std::out_of_range("Index exceeds the number of elements in the list");

        return FindBoxAt(Index)->Data;
    }

    ///
    /// Remove the element at the specified index in the list
    ///
    /// \exception std::out_of_range If the specified index is invalid
    ///
    void RemoveAt(size_t Index)
    {
        // If the index is invalid, throw an exception
        if (Index >= Size)
            throw std::out_of_range("Index exceeds the number of elements in the list");


        // Trying to remove the first element is equivalent to a call to RemoveHead()
        // Also here we handle the case when there is only one element in the list.
        if (Index == 0)
        {
            PopFront();
        }

        // Here we should have that:
        // (1) There are at least two elements in the list
        // (2) Index != 0
        // (3) We are not trying to remove the first element
        else
        {
            assert(this->GetSize() >= 2);

            // Find the box before the one we want to remove
            Box *pBoxBeforeIndex = FindBoxAt(Index - 1);

            // Make sure the Index is valid!
            assert(pBoxBeforeIndex != nullptr);

            // Get a pointer to the box that we want to remove
            Box *pBoxAtIndex = pBoxBeforeIndex->pNext;

            // If the box that we want to remove is the last one,
            // update the last element pointer accordingly
            if (Index == Size - 1)
                pLast = pBoxBeforeIndex;

            // Fix the next pointer of the previous box.
            pBoxBeforeIndex->pNext = pBoxAtIndex->pNext;

            // Delete the box
            delete pBoxAtIndex;

            // Decrement the size
            --Size;
        }
    }

    ///
    /// Return a new iterator for this list
    ///
    Iterator GetIterator() const
    {
        return Iterator(pFirst);
    }


private:
    ///
    /// Finds the box at a specific index in the list
    ///
    /// \return A pointer to the box, or nullptr, if there is no such index in the list
    ///
    Box* FindBoxAt(size_t Index) const
    {
        if (Index < 0 || Index >= this->Size)
            return nullptr;

        Box *p = pFirst;

        for (int i = 0; i < Index; ++i)
            p = p->pNext;

        return p;
    }
   

    ///
    /// Clones a chain of boxes
    ///
    /// The function receives a pointer to the first box
    /// in a chain of boxes and creates a new, identical chain.
    ///
    /// \param pFirstBox
    ///    Pointer to the first box in the chain to clone
    ///
    /// \param [out] pCloneStart
    ///    The function will use this parameter to return a pointer
    ///    to the first box in the cloned chain.
    ///    If the function fails, it will set the passed argument to nullptr.
    ///
    /// \param [out] pCloneEnd
    ///    The function will use this parameter to return a pointer
    ///    to the last box in the cloned chain.
    ///    If the function fails, it will set the passed argument to nullptr.
    ///
    static void CloneChain(Box* pFirstBox, Box*& pCloneStart, Box*& pCloneEnd)
    {
        pCloneStart = nullptr;
        pCloneEnd = nullptr;

        if (pFirstBox == nullptr)
            return;

        Box* pNewChain = nullptr;

        try
        {
            // Pointer to the start of the new chain
            pNewChain = new Box(pFirstBox->Data); 

            // Pointer to the element that we have to copy next
            Box* pReadFrom = pFirstBox->pNext;

            // Pointer to the element after which we have to copy the new element
            Box* pWriteAfter = pNewChain;

            while (pReadFrom)
            {
                pWriteAfter->pNext = new Box(pReadFrom->Data);
                pWriteAfter = pWriteAfter->pNext;
                pReadFrom = pReadFrom->pNext;
            }

            pCloneStart = pNewChain;
            pCloneEnd = pWriteAfter;
        }
        catch (std::bad_alloc&)
        {
            DestroyChain(pNewChain);
        }
    }


    ///
    ///    Destroys all boxes in a chain
    ///
    ///    \param [in] pFirstBox
    ///        A pointer to the first box in the chain.
    ///
    static void DestroyChain(Box* pFirstBox)
    {
        Box* pCurrent = pFirstBox;
        Box* pOld = pFirstBox;

        while (pCurrent)
        {
            pOld = pCurrent;
            pCurrent = pCurrent->pNext;
            delete pOld;
        }
    }

};

