/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <windows.h>

int main(int argc, char *argv[])
{
	// Ако потребителят не е указал коя папка да се сканира,
	// извежда се съобщение за това как да се използва програмата.
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <path>\n\n";
		return 1;
	}

	std::cout << "Scanning " << argv[1] << "...\n";

	// Поради улесняващите условия в задачата, считаме, че
	// всички файлове ще бъдат с път не по-дълъг от 260 символа,
	// колкото е стойността на MAX_PATH за Windows. 
	char path[MAX_PATH + 3];


	// При подаден път от вида C:\Temp\SomeDirectory,
	// конструира маска от вида C:\Temp\SomeDirectory\*
	// Ако потребителят подаде пътя накрая с наклонена черта,
	// например ето така: C:\Temp\SomeDirectory,
	// ще се конструира маска от вида C:\Temp\SomeDirectory\\*,
	// но това е ОК, защото системата ще го коригира.
	strcpy_s(path, MAX_PATH, argv[1]);
	strcat_s(path, MAX_PATH, "\\*");


	// Намираме първия файл в директорията
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(path, &ffd);

	// Ако операцията е била неуспешна, извеждаме съобщение за грешка
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "FindFirstFile failed! Error code is " << GetLastError() << std::endl;
		return 2;
	}


	// Извеждаме информация за всички файлове и директории,
	// които са били намерени в дадената.
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// Намереният елемент е директория
			std::cout << '\\' << ffd.cFileName << "\n";
		}
		else
		{
			// Поради улесняващите условия, считаме, че в директорията
			// няма нищо освен файлове или други поддиректории.
			// Например в нея няма да има soft links, junctions, и т.н.
			// Затова можем да считаме, че ако не влезем в if-клаузата,
			// намереният елемент е файл.
			// Също, за задачата считаме, че размерът на файловете, с които работим,
			// не е по-голям от 2^32 - 1.
			// Затова той се събира само в полето FileSizeLow на структурата.
			std::cout << ffd.cFileName << ", " << ffd.nFileSizeLow << " byte(s)\n";
		}

	} while (FindNextFile(hFind, &ffd) != 0);


	// От горния цикъл можем да излезем или ако възникне грешка,
	// или ако обходим всички елементи в директорията.
	// По-долу проверяваме дали второто е вярно.
	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		std::cout << "FindNextFile failed! Error code is " << GetLastError() << std::endl;
		return 3;
	}

	// Накрая трябва да се почисти.
	FindClose(hFind);

	return 0;
}
