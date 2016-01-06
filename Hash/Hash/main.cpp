/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <ctime>

#include "NotReallyHash.h"
#include "SeparateChainingHash.h"
#include "LinearProbingHash.h"


///
/// Sequentially fill pHash with all integers in [First, Last]
///
/// pszName is a string, which will be used as the name of the hash,
/// when printing information to STDOUT.
///
void FillSequence(Hash* pHash, int First, int Last, const char* pszName)
{
    std::cout
        << "Filling "
        << pszName
        << " with range ["
        << First
        << ", "
        << Last
        << "]...";

    time_t start = time(NULL);

    for (int i = First; i < Last; i++)
        pHash->Add(i);

    time_t end = time(NULL);

    std::cout << "completed in " << (end - start) << " second(s)\n";
}


///
/// Tests the search performance of pHash
///
/// The function sequentially looks up all values in [First, Last].
/// This is performed LoopsCount times.
///
/// pszName is a string, which will be used as the name of the hash,
/// when printing information to STDOUT.
///
void TestSearch(Hash* pHash, int First, int Last, int LoopsCount, const char* pszName)
{

	std::cout << "Testing " << pszName << std::endl;
	std::cout << "   Performing " << (LoopsCount * (Last - First)) << " searches...\n";

    int hitCount = 0;
    
    time_t start = time(NULL);

	for(int i = 0; i < LoopsCount; i ++)
	{
		for(int j = First ; j < Last; j++)
		{
			if(pHash->Search(j))
				hitCount++;
		}
	}

	time_t end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " second(s)\n";
	std::cout << "   Found " << hitCount << " element(s)\n\n";

}





int main()
{
    // Input benchmark parameters
    int ElementsToFill = 0;
    int LoopsCount = 0;

    std::cout << "How many elements to use: ";
    std::cin >> ElementsToFill;

    std::cout << "How many search loops to execute: ";
    std::cin >> LoopsCount;

    int ElementsToLookup = ElementsToFill * 2;
    
    std::cout
        << "Testing with " << ElementsToLookup << " elements per loop ("
        << ((ElementsToFill * 100) / (ElementsToLookup + ElementsToFill))
        << "% hits and "
        << ((ElementsToLookup * 100) / (ElementsToLookup + ElementsToFill))
        << "% misses)\n\n";


    // Create hash and hashing function objects
    NrhStl<std::list<int>> nrhList;
    NrhStl<std::vector<int>> nrhVector;
    NrhVectorWithBinarySearch nrhBinarySearch;

    ModularHashingFunction hashingFunctionA(7);
	ModularHashingFunction hashingFunctionB(1597);
    
    // These two functions scatter the hash values and are better suited for the Linear Probing hashes
    ModAndMultiplyHashingFunction hashingFunctionC(7, (ElementsToFill * 2 ) / 7);
    ModAndMultiplyHashingFunction hashingFunctionD(1000, (ElementsToFill * 2) / 1000);
	
    SeparateChainingHashStl schStlA(&hashingFunctionA, 7);
    SeparateChainingHashStl schStlB(&hashingFunctionB, 1597);
    SeparateChainingHash schA(&hashingFunctionA, 7);
	SeparateChainingHash schB(&hashingFunctionB, 1597);

	LinearProbingHash lphA(&hashingFunctionA, ElementsToFill);
	LinearProbingHash lphB(&hashingFunctionB, ElementsToFill);
    LinearProbingHash lphC(&hashingFunctionC, ElementsToFill);
    LinearProbingHash lphD(&hashingFunctionD, ElementsToFill);


	// Fill the hashes with data
    FillSequence(&nrhList, 0, ElementsToFill, "NrhStl<std::list>");
    FillSequence(&nrhVector, 0, ElementsToFill, "NrhStl<std::vector>");
    FillSequence(&nrhBinarySearch, 0, ElementsToFill, "NrhVectorWithBinarySearch");
    
    FillSequence(&schA, 0, ElementsToFill, "SeparateChainingHash with 7 chains");
    FillSequence(&schB, 0, ElementsToFill, "SeparateChainingHash with 1597 chains");
    FillSequence(&schStlA, 0, ElementsToFill, "SeparateChainingHashStl with 7 chains");
    FillSequence(&schStlB, 0, ElementsToFill, "SeparateChainingHashStl with 1597 chains");
    
    FillSequence(&lphA, 0, ElementsToFill, "LinearProbingHash with hashing function mod 7");
    FillSequence(&lphB, 0, ElementsToFill, "LinearProbingHash with hashing function mod 1597");
    FillSequence(&lphC, 0, ElementsToFill, "LinearProbingHash with hashing function mod 7 *");
    FillSequence(&lphD, 0, ElementsToFill, "LinearProbingHash with hashing function mod 1000 *");

    std::cout << "\n";


	// Test the search performance of hashes
	TestSearch(&nrhList, 0, ElementsToLookup, LoopsCount, "NrhStl<std::list>");
    TestSearch(&nrhVector, 0, ElementsToLookup, LoopsCount, "NrhStl<std::vector>");
    TestSearch(&nrhBinarySearch, 0, ElementsToLookup, LoopsCount, "NrhVectorWithBinarySearch");

    TestSearch(&schA, 0, ElementsToLookup, LoopsCount, "SeparateChainingHash with 7 chains");
	TestSearch(&schB, 0, ElementsToLookup, LoopsCount, "SeparateChainingHash with 1597 chains");
    TestSearch(&schStlA, 0, ElementsToLookup, LoopsCount, "SeparateChainingHashStl with 7 chains");
    TestSearch(&schStlB, 0, ElementsToLookup, LoopsCount, "SeparateChainingHashStl with 1597 chains");

    TestSearch(&lphA, 0, ElementsToLookup, LoopsCount,  "LinearProbingHash with hashing function mod 7");
	TestSearch(&lphB, 0, ElementsToLookup, LoopsCount,  "LinearProbingHash with hashing function mod 1597");
    TestSearch(&lphC, 0, ElementsToLookup, LoopsCount, "LinearProbingHash with hashing function mod 7 *");
    TestSearch(&lphD, 0, ElementsToLookup, LoopsCount, "LinearProbingHash with hashing function mod 1597 *");

	return 0;
}
