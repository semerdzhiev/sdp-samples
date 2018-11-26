/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "BinarySearchTree.h"

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> sample{ 1, 10, -1, 50, 11 };
    BinarySearchTree<int> tree;

    for (auto it = sample.begin(); it != sample.end(); ++it)
        tree.Insert(*it);

    for (auto it = tree.GetIterator(); !it.EndReached(); it.MoveNext())
        std::cout << it.Current() << " ";

    std::cout << std::endl;
}