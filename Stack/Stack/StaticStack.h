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
/// The underlying buffer is allocated on the stack.
///
/// \tparam TYPE
///    Type of the elements stored in the stack
///
/// \tparam MAX_SIZE
///    Maximum number of elements that can be stored
///    in the stack
///
template <typename TYPE, int MAX_SIZE>
class StaticStack {
private:
    TYPE Data[MAX_SIZE]; /// Stores the stack elements
    size_t Size;         /// Number of elements stored in the stack

public:
    
    ///
    /// Constructs an empty stack
    ///
    StaticStack()
        : Size(0)
    {}


    ///
    /// Pushes an element on the stack
    ///
    /// \exception std::exception If the stack overflows
    ///
    void Push(const TYPE & Element)
    {
        if (Size >= MAX_SIZE)
            throw std::exception();

        Data[Size++] = Element;
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
            Element = Data[--Size];
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
        if(Size > 0)
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

        return Data[Size - 1];
    }

    const TYPE& Peek() const
    {
        if (Size == 0)
            throw std::exception();

        return Data[Size - 1];
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


    /// Returns the maximum number of elements
    /// that can be stored in the stack
    ///
    size_t GetMaxSize() const
    {
        return MAX_SIZE;
    }


    /// Checks whether the stack is empty
    ///
    bool IsEmpty() const
    {
        return Size == 0;
    }
};
