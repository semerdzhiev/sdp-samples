/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <exception>

///
/// An linked implementation of a FILO stack
///
/// The size of the stack grows and shrinks dynamically
/// depending on the number of stored elements.
/// Memory for the stack's elements is allocated on the heap.
///
/// \tparam TYPE
///    Type of the elements stored in the stack
///
template <typename TYPE>
class LinkedStack {

    class Box {
	public:
		TYPE Data;
		Box* pNext;
        
        Box(const TYPE& Data, Box* pNext = NULL)
            : Data(Data), pNext(pNext)
        {
        }
	};

private:
    Box* pTop;   /// Pointer to the top of the stack
    size_t Size; /// Number of elements in the stack

public:
    ///
    /// Constructs an empty stack
    ///
    LinkedStack()
    {
        ZeroVariables();
    }

    ///
    /// Destructor
    ///
    ~LinkedStack()
    {
        Destroy();
    }

    ///
    /// Copy construtor
    ///
    /// \exception std::bad_alloc If memory allocation fails
    ///
    LinkedStack(LinkedStack const & Other)
    {
        ZeroVariables();
        CopyFrom(Other); // CopyFrom cleans up all resouces
                         // if copying fails
    }

    ///
    /// The operator frees the currently allocated memory first
    /// and after that performs the copying.
    /// If copying fails, the stack will be left empty.
    ///
    /// \exception std::bad_alloc If memory allocation fails
    ///
	LinkedStack& operator=(const LinkedStack & Other)
    {
        if (this != &Other)
        {
            Destroy();
            CopyFrom(Other);
        }

        return *this;
    }

public:
    ///
    /// Pushes a new element on the stack
    ///
    /// \exception std::bad_alloc If memory allocation fails
    ///
    void Push(const TYPE & Element)
    {
        pTop = new Box(Element, pTop);
        ++Size;
    }

    ///
    /// Removes and returns the element on top of the stack
    ///
    /// \param [out] Element
    ///    A parameter, which will receive the value of the top element.
    ///    If the stack is empty, this element will not be altered.
    ///
    /// \return
    ///    true if the operation was successful or
    ///    false if the stack was empty.
    ///
    bool Pop(TYPE& Element)
    {
        if (Size == 0)
            return false;

        Element = pTop->Data;

        Pop();

        return true;
    }


    ///
    /// Removes the element on the top of the stack
    ///
    /// If the stack is empty, the function does nothing
    ///
    void Pop()
    {
        if (pTop)
        {
            Box* pOld = pTop;
            pTop = pTop->pNext;
            delete pOld;
            --Size;
        }
    }

    
    ///
    /// Retrieves the element on the top of the stack
    ///
    /// \exception std::exception If the stack is empty
    ///
    TYPE& Peek()
    {
        if (Size == 0)
            throw std::exception();

        return pTop->Data;
    }

    const TYPE& Peek() const
    {
        if (Size == 0)
            throw std::exception();

        return pTop->Data;
    }


    ///
    /// Empties the stack
    ///
    /// The function removes all elements and
    /// frees the memory allocated for the stack.
    ///
    void Clear()
    {
        Destroy();
    }

    ///
    /// Returns the number of elements currently stored in the stack
    ///
    size_t GetSize() const
    {
        return Size;
    }
    
    ///
    /// Checks whether the stack is empty
    ///
    bool IsEmpty() const
    {
        return Size == 0;
    }

private:
    ///
    /// Assigns initial values for the data-members of the object
    ///
    /// The values are proper for an empty stack for which no memory
    /// is allocated. e.g. on construction or after freeing the memory.
    ///
    void ZeroVariables()
    {
        pTop = 0;
        Size = 0;
    }

    ///
    /// Empties the stack and frees the allocated memory
    ///
    void Destroy()
    {
        Box* p;

        while (pTop)
        {
            p = pTop;
            pTop = pTop->pNext;
            delete p;
        }

        ZeroVariables();
    }

    ///
    /// Makes the current object a copy of another one
    ///
    /// The function assumes that the object is empty
    /// (i.e. no memory is allocated for it)
    ///
    /// \param Other
    ///    Object to copy from. Can be either empty or non-empty
    ///
    /// \exception std::bad_alloc
    ///    If the copy operation fails
    ///
    void CopyFrom(const LinkedStack & Other)
    {
        if (Other.IsEmpty())
            return;

        Box *ours, *theirs;

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

            Size = Other.Size;
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

};
