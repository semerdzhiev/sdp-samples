/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

///
/// An implementation of a FILO stack
///
/// The maximum size of the stack is fixed and cannot be changed.
/// The underlying buffer is allocated on the heap.
///
/// \tparam TYPE
///    Type of the elements stored in the stack
///
template <typename TYPE>
class FixedSizeStack {
private:
    TYPE* pData;       /// Pointer to the stack's contents
    size_t BufferSize; /// Size of the allocated buffer
    size_t Size;       /// Number of elements currently stored in the array

public:
    ///
    /// Constructs an empty stack
    ///
    FixedSizeStack(size_t Size)
    {
        ZeroVariables();
        pData = new TYPE[Size];
        BufferSize = Size;
    }

    ///
    /// Destroys a stack
    ///
    ~FixedSizeStack()
    {
        Destroy();
    }

    ///
    /// Copy constructor
    ///
    FixedSizeStack(const FixedSizeStack & Other)
    {
        ZeroVariables();
        CopyFrom(Other);
    }

    ///
    /// Assignment operator
    /// 
    FixedSizeStack& operator=(const FixedSizeStack & Other)
    {
        if (this != &Other)
        {
            Destroy();
            CopyFrom(Other);
        }

        return *this;
    }


    ///
    /// Pushes an element on the stack
    ///
    /// \exception std::exception If the stack overflows
    ///
    void Push(const TYPE & Element)
    {
        if (Size >= BufferSize)
            throw std::exception();

        pData[Size++] = Element;
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
        if (Size > 0)
        {
            Element = pData[--Size];
            return true;
        }

        return false;
    }


    ///
    /// Removes the element on the top of the stack
    ///
    /// If the stack is empty, the function does nothing
    ///
    void Pop()
    {
        if (Size > 0)
            --Size;
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

        return pData[Size - 1];
    }

    const TYPE& Peek() const
    {
        if (Size == 0)
            throw std::exception();

        return pData[Size - 1];
    }

    
    ///
    /// Empties the stack
    ///
    /// The function removes all elements, but does not
    /// free the memory allocated for the stack.
    ///
    void Clear()
    {
        Size = 0;
    }

    ///
    /// Returns the number of elements currently stored in the stack
    ///
    size_t GetSize() const
    {
        return Size;
    }

    ///
    /// Returns the maximum number of elements
    /// that can be stored in the stack
    ///
    size_t GetMaxSize() const
    {
        return BufferSize;
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
        pData = nullptr;
        BufferSize = 0;
        Size = 0;
    }

    ///
    /// Empties the stack and frees the allocated memory
    ///
    void Destroy()
    {
        delete[] pData;
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
    void CopyFrom(FixedSizeStack const & Other)
    {
        if (Other.IsEmpty())
            return;

        pData = new TYPE[Other.BufferSize];
        BufferSize = Other.BufferSize;
        Size = Other.Size;

        for (size_t i = 0; i < Size; i++)
            pData[i] = Other.pData[i];
    }

};