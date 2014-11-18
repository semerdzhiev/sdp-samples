#include <iostream>
#include "UnitTestFramework.h"



///
/// Регистрира подадената като аргумент функция като тестваща функция
///
Registrator::Registrator(PTESTFN fn)
{
	GetRegisteredFunctions().push_back(fn);
}


///
/// Използваме функция, вместо статична член-данна, за да избегнем
/// т.нар. "static initialization order fiasco":
/// http://www.parashift.com/c++-faq/static-init-order.html
///
/// Решението е базирано на:
/// http://www.parashift.com/c++-faq/static-init-order-on-first-use.html
/// разликата е, че няма нужда да заделяме паметта динамично, защото няма
/// да имаме проблем при унищожаването на статичните данни, а само
/// при тяхната инициализация:
/// http://www.parashift.com/c++-faq/construct-on-first-use-v2.html
///
std::vector<PTESTFN>& Registrator::GetRegisteredFunctions()
{
	static std::vector<PTESTFN> registeredFunctions;

	return registeredFunctions;
}


///
/// Стартира една по една всички регистрирани тестващи функции.
///
/// Функциите се изпълняват в реда, в който са били регистрирани.
///
void Registrator::RunTests()
{
	std::vector<PTESTFN>& tests = GetRegisteredFunctions();

	// Общ брой тестове
	size_t NumTests = tests.size();
	
	// Указател към текуща тестваща функция
	PTESTFN pfn;

	// Резултат от тестовете
	bool result;

	for (size_t i = 0; i < NumTests; i++)
	{
		pfn = tests[i];

		std::cout << "Running test " << i << "...\n";
		
		// Резултатът е true...
		result = true;

		try {
			pfn();
		}
		catch (...)	{
			// ...освен ако тестът не хвърли изключение
			result = false;
		}
		
		std::cout << "  Status: " << (result ? "Passed" : "Failed");
		std::cout << "\n\n";
	}
}


///
/// Функцията main() е "скрита" в рамката за тестове
///
int main()
{
	std::cout << "Testing started:\n\n";
	
	// Стартираме регистрираните тестове
	Registrator::RunTests();

	std::cout << "All done.\n\n";

	return 0;
}
