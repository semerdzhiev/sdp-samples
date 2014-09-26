#include <iostream>

#include "DynamicArray.h"

int main()
{
	DynamicArray da;

	//
	// 1: Добавяме елементи в масива
	//
	std::cout << "Adding numbers to the array: ";

	for(int i = 0; i < 10; i++)
	{
		
		da.Add(i);
		std::cout << i << ", ";
	}

	std::cout << "done\n\n";


	//
	// 2: Извеждаме елементите с помощта на оператора []
	//
	std::cout << "The array contains: " << da[0];

	for(size_t i = 1; i < da.GetLength(); i++)
	{
		std::cout << ", " << da[i];
	}

	std::cout << "\n\n";
	

	//
	// 3: Променяме елементите с помощта на оператора []
	//
	std::cout << "Multiplying each array element by 10...\n";

	for(size_t i = 0; i < da.GetLength(); i++)
	{
		// По-долу не можем да използваме оператора *=,
		// тъй като той не е дефиниран за DynamicArrayElementProxy
		// (въпреки, че можем да го направим, ако е нужно)
		da[i] = da[i] * 10;
	}

	da.Print();
	std::cout << "\n";


	//
	// 4: Опит за работа с константен масив
	//
	std::cout << "Let's go constant!\n";

	const DynamicArray & cda = da;

	std::cout << "The fifth element is " << cda[5] << "\n\n"; // този код е коректен...

	// ...но даденият в по-долния коментар няма да се компилира:
	// cda[5] = 10;


	//
	// 5: Опит за достъп до невалиден индекс
	//
	std::cout << "Trying to access an invalid index...\n";

	try
	{
		da.GetAt(da.GetLength() + 1);
	}
	catch(std::out_of_range& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}

