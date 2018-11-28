/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <algorithm>

#include "NotReallyHash.h"


///
/// Add an element to the container
///
/// The element is placed at the end of the
/// underlying STL collection by using push_back.
///
template <class Container>
bool NrhStl<Container>::Add(const int Value)
{
    data.push_back(Value);
    return true;
}


///
/// Looks up the element in the collection
///
/// The function does this by an exhaustive search.
///
template <class Container>
bool NrhStl<Container>::Search(const int Value)
{
    for (auto it = data.cbegin(); it != data.cend(); it++)
    {
        if (*it == Value)
            return true;
    }

    return false;
}


///
/// Print information
///
template <class Container>
void NrhStl<Container>::PrintInfo() const
{
    std::cout << "NrhStl:";

    PrintCommonInfo(data.size(), memoryUsed);
}


///
/// Specialization of the PrintInfo function for std::list<int>
///
template <>
void NrhStl< std::list<int> >::PrintInfo() const
{
    // NOTE: Microsoft specific. Assumes we are storing int elements
    // and using the default allocator.
    static const size_t stlListNodeSize = sizeof(std::_List_node<int, void*>);

    size_t memoryUsed =
        sizeof(*this) +  // object size
        data.size() * stlListNodeSize; // nodes allocated by the list

    std::cout << "NrhStl<std::list<>>:";

    PrintCommonInfo(data.size(), memoryUsed);
}



///
/// Specialization of the PrintInfo function for std::vector<int>
///
template <>
void NrhStl< std::vector<int> >::PrintInfo() const
{
    size_t memoryUsed = data.capacity() * sizeof(int);

    std::cout << "NrhStl<std::vector<>>:";

    PrintCommonInfo(data.size(), memoryUsed);
}



///
/// Add an element to the container
///
/// The operation keeps the underlying STL vector sorted.
///
bool NrhVectorWithBinarySearch::Add(const int Value)
{
    data.insert(std::upper_bound(data.begin(), data.end(), Value), Value);

    return true;
}



///
/// Looks up the element in the vector by using binary search
///
bool NrhVectorWithBinarySearch::Search(const int Value)
{
    return std::binary_search(data.begin(), data.end(), Value);
}



///
/// Print information about the collection
///
void NrhVectorWithBinarySearch::PrintInfo() const
{
    size_t memoryUsed = data.capacity() * sizeof(int);

    std::cout << "NrhVectorWithBinarySearch:";

    PrintCommonInfo(data.size(), memoryUsed);
}

template class NrhStl< std::list<int> >;
template class NrhStl< std::vector<int> >;