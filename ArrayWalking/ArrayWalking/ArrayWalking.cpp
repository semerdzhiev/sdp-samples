/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <ctime>
#include <iostream>

int main()
{
	const size_t RowsCount = 3000;
	const size_t ColsCount = 300000;

	int *parr = new int[RowsCount * ColsCount];

	size_t row, col;
	unsigned long long sum;
	time_t start, end;

	//
	// Initialize the elements of the array
	//
	std::cout << "Initalizing the elements of the array...";
	start = std::time(NULL);

	for (row = 0; row < RowsCount; ++row)
		for (col = 0; col < ColsCount; ++col)
			parr[ColsCount * row + col] = static_cast<int>(row);

	end = std::time(NULL);
	std::cout << "\n    execution took " << end - start << " second(s)\n\n";


	//
	// Iterate over the columns and then the rows and then the columns
	//
	std::cout << "Iterating by columns and then rows...";

	sum = 0;
	start = std::time(NULL);

	for (col = 0; col < ColsCount; ++col)
		for (row = 0; row < RowsCount; ++row)
			sum += parr[ColsCount * row + col];

	end = std::time(NULL);
	std::cout << "\n    execution took " << end - start << " second(s)\n    sum is " << sum << "\n\n";


	//
	// Iterate over the rows and then the columns
	//
	std::cout << "Iterating by rows and then columns...";

	sum = 0;
	start = std::time(NULL);

	for (row = 0; row < RowsCount; ++row)
		for (col = 0; col < ColsCount; ++col)
			sum += parr[ColsCount * row + col];

	end = std::time(NULL);
	std::cout << "\n    execution took " << end - start << " second(s)\n    sum is " << sum << "\n\n";

	delete[] parr;

	return 0;
}