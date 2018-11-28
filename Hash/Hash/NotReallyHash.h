/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
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
private:
	Container data;

public:
	bool Add(const int Value) override;
	bool Search(const int Value) override;
	void PrintInfo() const override;
};



///
/// Implements the functionality of a hash by
/// using a sorted array and binary search
///
class NrhVectorWithBinarySearch : public Hash
{
private:
    std::vector<int> data;

public:
    bool Add(const int Value) override;
    bool Search(const int Value) override;
    void PrintInfo() const override;
};