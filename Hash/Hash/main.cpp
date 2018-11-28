/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
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


class HashBenchmark
{
    int elementsToFill;
    int elementsToLookup;
    int loopsCount;

    ///
    /// Sequentially fill a pHash with all integers in [0, elementsToFill]
    ///
    /// pszName is a string, which will be used as the name of the hash,
    /// when printing information to STDOUT.
    ///
    /// \return
    ///    Amount of time in seconds, it took to fill the hash
    ///
    time_t Fill(Hash& hash, const char* pszName) const
    {
        time_t start = time(nullptr);

        for (int i = 0; i < elementsToFill; i++)
        {
            hash.Add(i);
            //hash.Add(rand());
        }

        time_t end = time(nullptr);

        return end - start;
    }


    ///
    /// Tests the search performance of a hash
    ///
    /// The function sequentially looks up all values in [0, elementsToLookup].
    /// This is performed loopsCount times.
    ///
    /// pszName is a string, which will be used as the name of the hash,
    /// when printing information to STDOUT.
    ///
    time_t Lookup(Hash& hash, const char* pszName) const
    {
        int hitCount = 0;

        time_t start = time(nullptr);

        for (int i = 0; i < loopsCount; i++)
        {
            for (int j = 0; j < elementsToLookup; j++)
            {
                if (hash.Search(j))
                    hitCount++;
            }
        }

        time_t end = time(nullptr);

        return end - start;
    }

public:
    HashBenchmark(int elementsToFill, int loopsCount)
        : elementsToFill(elementsToFill),
          elementsToLookup(elementsToFill * 2), // half of the searches will be misses
          loopsCount(loopsCount)
    {
        // Nothing to do here
    }

    void Process(Hash& hash, const char* name)
    {
        time_t f = Fill(hash, name);
        time_t l = Lookup(hash, name);
        
        std::cout << name << " (" << f << "/" << l << ")\n\n";
    }

    void PrintInfo() const
    {
        std::cout << "\nBenchmark information:";
        std::cout << "\n   Each hash will be filled with the integers in [0, " << elementsToFill << "]";
        std::cout << "\n   Searching will perform " << elementsToLookup << " lookups";
        std::cout << "\n   Data is printed in the following format: hash name (fill time/lookup time)";
        std::cout << "\n\n";
    }
};


int main()
{
    //std::cout.imbue(std::locale("en_US"));

    int elementsToFill = 0; // Number of elements to fill in each hash
    int loopsCount = 1;     // How many times to repeat each operation
       
    std::cout << "How many elements to use: ";
    std::cin >> elementsToFill;

    int low = elementsToFill / 20; // 5% of sample size
    int high = elementsToFill / 2; // 50% of sample size
    std::cout << "Using " << low << "/" << high << " chains\n";

    HashBenchmark test(elementsToFill, loopsCount);
    test.PrintInfo();

    ModularHashingFunction modLow(low);
	ModularHashingFunction modHigh(high);
    
    // These two functions scatter the hash values and are better suited for the Linear Probing hashes
    ModAndMultiplyHashingFunction spreadLow(low, (elementsToFill * 2 ) / low);
    ModAndMultiplyHashingFunction spreadHigh(high, (elementsToFill * 2) / high);

    test.Process(NrhStl<std::list<int>>(), "NrhStl<std::list>");
    test.Process(NrhStl<std::vector<int>>(), "NrhStl<std::vector>");
    test.Process(NrhVectorWithBinarySearch(), "NrhVectorWithBinarySearch");
    
    test.Process(SeparateChainingHashStl(&modLow, low),    "SeparateChainingHashStl w/ modLow");
    test.Process(SeparateChainingHashStl(&modHigh, high), "SeparateChainingHashStl w/ modHigh");
    test.Process(SeparateChainingHash(&modLow, low),       "SeparateChainingHash w/ modLow");
    test.Process(SeparateChainingHash(&modHigh, high),    "SeparateChainingHash w/ modHigh");
    
    test.Process(LinearProbingHash(&modLow, elementsToFill), "LinearProbingHash /w modLow");
    test.Process(LinearProbingHash(&modHigh, elementsToFill), "LinearProbingHash /w modHigh");
    test.Process(LinearProbingHash(&spreadLow, elementsToFill), "LinearProbingHash /w spreadLow");
    test.Process(LinearProbingHash(&spreadHigh, elementsToFill), "LinearProbingHash /w spreadHigh");

	return 0;
}
