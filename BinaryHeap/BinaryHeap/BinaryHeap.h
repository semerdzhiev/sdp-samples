/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <set>
#include <vector>
#include <functional>

template <typename ElementType, typename Compare = std::less<ElementType> >
class BinaryHeap
{
    std::vector<ElementType> data; /// Stores the elements of the heap
    Compare comesBefore;           /// A predicate used to compare the elements of the heap

public:

    BinaryHeap() = default;

    BinaryHeap(Compare predicate) : comesBefore(predicate)
    { /* Nothing to do here */ }

    BinaryHeap(const BinaryHeap&) = default;
    BinaryHeap& operator=(const BinaryHeap&) = default;
    BinaryHeap(BinaryHeap&&) = default;
    BinaryHeap& operator=(BinaryHeap&&) = default;

    ///
    /// Add a new element to the heap
    ///
    void Insert(const ElementType& item)
    {
        data.push_back(item);

        size_t i = data.size() - 1;

        while (i > 0 && comesBefore(data[i], data[parent(i)]))
        {
            std::swap(data[parent(i)], data[i]);
            i = parent(i);
        }
    }


    ///
    /// Removes the top of the heap
    ///
    void Extract()
    {
        if (data.empty())
            return;

        data[0] = data.back();
        data.pop_back();

        size_t i = 0;
        size_t s = leftChild(i);

        while (s < data.size())
        {
            if (s < data.size() - 1 && comesBefore(data[s + 1], data[s]))
                ++s; // if the right successor exists and comes before the left in the order, set s to its index.

                        // Here we have: s is the index of that successor of data[i], which comes first in the order

            if (!comesBefore(data[s], data[i]))
                break;

            std::swap(data[i], data[s]);
            i = s;
            s = leftChild(s);
        }
    }

    ElementType& Top()
    {
        if (data.size() == 0)
        throw std::exception();

        return data[0];
    }

    const ElementType& Top() const
    {
        return Top();
    }

    size_t Size() const
    {
        return data.size();
    }

    bool Empty() const
    {
        return data.empty();
    }

    void Print() const
    {
        for (auto it = data.begin(); it != data.end(); ++it)
            std::cout << *it << ", ";

        std::cout << "\n";
    }

private:

    static size_t parent(size_t index)
    {
        return (index - 1) / 2;
    }

    static size_t leftChild(size_t index)
    {
        return index * 2 + 1;
    }
};
