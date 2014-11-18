#pragma once

#include <vector>

/// Указател към функция, която провежда тестове
typedef void(*PTESTFN)();


///
/// Клас, в който могат да се регистрират и
/// след това изпълняват тестващи функции
///
class Registrator
{
private:
	static std::vector<PTESTFN>& GetRegisteredFunctions();

public:
	Registrator(PTESTFN fn);
	static void RunTests();
};


/// Регистрира тестваща функция и започва нейната дефиниция
#define TEST_FUNCTION(FNNAME)				\
void FNNAME();								\
Registrator testobj___##FNNAME(FNNAME);		\
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
