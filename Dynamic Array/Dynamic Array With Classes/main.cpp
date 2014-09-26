#include <iostream>
#include <time.h>

#include "DynamicArray.h"

int main()
{
	std::cout << "Entering main()\n";

	DynamicArray da;

	//
	// 1: Добавяме елементи в масива
	//
	std::cout << "-= 1 =-\n";

	// Брой на елементите, които ще бъдат добавени
	const size_t ELEMENTS_COUNT = 2000;

	time_t then = time(NULL);

	for(int i = 0; i < ELEMENTS_COUNT; i++)
	{
		da.Add(i);
	}

	time_t now = time(NULL);


	std::cout
		<< "Filling the array with " << ELEMENTS_COUNT
		<< " element(s) took " << (now - then) << " second(s)\n";


	da.Print();

	//
	// 2: Оператор за събиране
	//
	std::cout << "-= 2 =-\n";

	DynamicArray test1;

	test1 = da + da;

	test1.Print();


	//
	// 3: Оператор за присвояване
	//
	std::cout << "-= 3 =-\n";

	DynamicArray  test2(da);

	test2.Print();

	std::cout << "Leaving main()\n";

	return 0;
}

