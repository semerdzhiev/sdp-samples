/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <vector>
#include <iostream>
#include <string>

/// Указател към функция, която провежда тестове
typedef void(*PTESTFN)();


/// Съдържа информация за една тестваща функция
class TestFunctionInfo
{
public:
	TestFunctionInfo(PTESTFN pfn, const char* Tag);

	/// Указател към функцията
	PTESTFN pfn;

	/// Кратък текст описващ функцията
	std::string Tag;
};


///
/// Клас, в който могат да се регистрират и
/// след това изпълняват тестващи функции
///
class Registrator
{
private:
	static std::vector<TestFunctionInfo>& GetRegisteredFunctions();

public:
	Registrator(const TestFunctionInfo &);
	static void RunTests();
};


/// Регистрира тестваща функция и започва нейната дефиниция
#define TEST_FUNCTION(FNNAME)										\
void FNNAME();														\
Registrator testobj___##FNNAME(TestFunctionInfo(FNNAME, #FNNAME));	\
void FNNAME()								


///
/// Оценява даден израз и проверява дали той се свежда до true
/// Ако това не е така, в STDERR се извежда съобщение и се
/// излиза от тестващата функция
///
/// \warning
///		Обърнете внимание, че за да може проверката да прекрати
///		изпълнението на теста на произволно ниво в кода, тя хвърля
///		изключение.
///
#define TEST(code)										\
	if( ! (code) ) {									\
		std::cout << "FAIL: " << #code << std::endl;	\
		throw(false);									\
	}
