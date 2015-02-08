#include <iostream>
#include <time.h>

#include "NotReallyHash.h"
#include "SeparateChainingHash.h"
#include "LinearProbingHash.h"

const size_t ELEMENTS_IN_HASH = 1000;

void TestSearch(Hash* pHash, const char* pszName)
{
	const size_t LOOPS_COUNT = 5;
	const size_t LOOP_LIMIT = ELEMENTS_IN_HASH *2; // equal number of hits and misses
	
	std::cout << "Testing " << pszName << std::endl;
	std::cout << "   Performing " << (LOOPS_COUNT * LOOP_LIMIT) << " searches...\n";

	time_t start = time(NULL);

	int found = 0;

	for(int i = 0; i < LOOPS_COUNT; i ++)
	{
		for(int j = 0 ; j < LOOP_LIMIT; j++)
		{
			if(pHash->Search(j))
			{
				found++;
			}		
		}
	}

	time_t end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " second(s)\n";
	std::cout << "   Found " << found << " element(s)\n\n";

}


int main()
{
	ModularHashingFunction hashingFunctionA(7);
	ModularHashingFunction hashingFunctionB(1597);

	NotReallyHash nrh;
	
	SeparateChainingHash schA(&hashingFunctionA, 7);
	SeparateChainingHash schB(&hashingFunctionB, 1597);

	LinearProbingHash lphA(&hashingFunctionA, ELEMENTS_IN_HASH);
	LinearProbingHash lphB(&hashingFunctionB, ELEMENTS_IN_HASH);

	// Fill the hashes with data

	std::cout << "Adding " << ELEMENTS_IN_HASH << " elements to the hashes\n";

	for(size_t i = 0; i < ELEMENTS_IN_HASH; i++)
	{
		nrh.Add(i);
		schA.Add(i);
		schB.Add(i);
		lphA.Add(i);
		lphB.Add(i);

		std::cout << "\r" << (((double)i * 100) / ELEMENTS_IN_HASH) << "%";
	}

	std::cout << std::endl << std::endl;

	nrh.PrintInfo();
	schA.PrintInfo();
	schB.PrintInfo();
	lphA.PrintInfo();
	lphB.PrintInfo();

	std::cout << std::endl;

	// Now test the hashes for performance
	TestSearch(&nrh, "Regular linked list");
	TestSearch(&schA, "SeparateChainingHash with 7 chains");
	TestSearch(&schB, "SeparateChainingHash with 1597 chains");
	TestSearch(&lphA, "LinearProbingHash with hashing function mod 7");
	TestSearch(&lphB, "LinearProbingHash with hashing function mod 1597");

	return 0;
}
