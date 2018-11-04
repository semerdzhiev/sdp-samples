/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <vector>

template <typename TYPE>
class StackAsAdapter
{
    std::vector<TYPE> data;

public:

    void Push(const TYPE & Element)
    {
        data.push_back(Element);
    }

    bool Pop(TYPE& Element)
    {
        if ( ! data.empty())
        {
            Element = data.back();
            data.pop_back();
            return true;
        }

        return false;
    }

    void Pop()
    {
        if (! data.empty())
            data.pop_back();
    }

    TYPE& Peek()
    {
        if (data.empty())
            throw std::exception();

        return data.back();
    }

    const TYPE& Peek() const
    {
        return const_cast<StackAsAdapter*>(this)->Peek();
    }

    void Clear()
    {
        data.clear();
    }

    size_t GetSize() const
    {
        return data.size();
    }

    size_t GetMaxSize() const
    {
        return data.max_size();
    }

    ///
    /// Checks whether the stack is empty
    ///
    bool IsEmpty() const
    {
        return data.empty();
    }
};