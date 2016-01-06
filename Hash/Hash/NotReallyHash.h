/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <list>
#include <vector>

#include "Hash.h"


///
/// Provides the functionality of a hash, but does
/// not implement a hash data structure and algorithms.
///
/// The class uses one of the standard STL containers.
/// It is used as a reference, when comparing
/// the performance of a hash algorithm, vs. other
/// data structures.
///
template <class Container>
class NrhStl : public Hash
{
public:
	virtual bool Add(const int Value);
	virtual bool Search(const int Value);
	virtual void PrintInfo() const;

private:
	Container Data;
};



///
/// Implements the functionality of a hash by
/// using a sorted array and binary search
///
class NrhVectorWithBinarySearch : public Hash
{
public:
    virtual bool Add(const int Value);
    virtual bool Search(const int Value);
    virtual void PrintInfo() const;

private:
    std::vector<int> Data;
};