#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <cstring>

///
/// Asserts different types of conditions and performs actions
/// based on the outcome
///
class Assert
{
private:
    ///
    /// Checks whether a condition is true and throws an exception if not
    ///
    static void AssertCondition(bool Condition)
    {
        if (!Condition)
        {
            throw std::exception();
        }
    }

public:
    ///
    /// Tests whether two values of the same type are equal using the assignment operator (==)
    ///
    template <typename T>
    static void AreEqual(const T& left, const T& right)
    {
        AssertCondition(left == right);
    }

    ///
    /// Tests whether two values of different types are equal using the assignment operator (==)
    ///
    template <typename T, typename U>
    static void AreEqual(const T& left, const U& right)
    {
        AssertCondition(left == right);
    }


    ///
    /// Tests whether two C-style strings are equal
    ///
    static void AreEqual(const char* left, const char* right)
    {
        AssertCondition(strcmp(left, right) == 0);
    }


    ///
    /// Tests whether two float values are equal,
    /// i.e. their difference is less than or equal to a specific delta
    ///
    static void AreEqual(const float& left, const float& right, double delta = 0.0001)
    {
        AssertCondition(fabs(left - right) <= fabs(delta));
    }


    ///
    /// Tests whether two double values are equal,
    /// i.e. their difference is less than or equal to a specific delta
    ///
    static void AreEqual(const double& left, const double& right, double delta = 0.0001)
    {
        AssertCondition(fabs(left - right) <= fabs(delta));
    }


    ///
    /// Tests whether two values of the same type are equal using a negation of the assignment operator (==)
    ///
    template <typename T>
    static void AreNotEqual(const T& left, const T& right)
    {
        AssertCondition( ! (left == right));
    }

    ///
    /// Tests whether two values of different types are equal using a negation of the assignment operator (==)
    ///
    template <typename T, typename U>
    static void AreNotEqual(const T& left, const U& right)
    {
        AssertCondition( ! (left == right));
    }


    ///
    /// Tests whether two C-style strings are not equal
    ///
    static void AreNotEqual(const char* left, const char* right)
    {
        AssertCondition(strcmp(left, right) != 0);
    }


    ///
    /// Tests whether two float values are not equal,
    /// i.e. their difference exceeds a specific delta
    ///
    static void AreNotEqual(const float& left, const float& right, double delta = 0.0001)
    {
        AssertCondition(fabs(left - right) > fabs(delta));
    }


    ///
    /// Tests whether two double values are not equal,
    /// i.e. their difference exceeds a specific delta
    ///
    static void AreNotEqual(const double& left, const double& right, double delta = 0.0001)
    {
        AssertCondition(fabs(left - right) > fabs(delta));
    }


    ///
    /// Checks whether a pointers is NULL
    ///
    template <typename T>
    static void IsNull(const T* p)
    {
        AssertCondition(p == NULL);
    }


    ///
    /// Checks whether a pointers is not NULL
    ///
    template <typename T>
    static void IsNotNull(const T* p)
    {
        AssertCondition(p != NULL);
    }


    ///
    /// Checks whether a condition is true
    ///
    static void IsTrue(bool Condition)
    {
        AssertCondition(Condition);
    }


    ///
    /// Checks whether a condition is false
    ///
    static void IsFalse(bool Condition)
    {
        AssertCondition( ! Condition);
    }


    ///
    /// Always fails
    ///
    static void Fail()
    {
        AssertCondition(false);
    }


	///
	/// Checks whether the comparison operators behave like a strict relation
	/// regarding an element A of type T
	///
	template <typename T>
	static void AreComparisonOperatorsStrict(const T& A)
	{
		AssertCondition(A == A);
		AssertCondition(!(A != A));

		AssertCondition(A <= A);
		AssertCondition(A >= A);

		AssertCondition(!(A < A));
		AssertCondition(!(A > A));
	}


	///
	/// Checks whether the comparison operators behave like a strict relation
	/// regarding two different elements A and B of type T, who are not considered equal
	///
	template <typename T>
	static void AreComparisonOperatorsStrictForDifferingElements(const T& A, const T& B)
	{
		AssertCondition(!(A == B));
		AssertCondition(!(B == A));

		AssertCondition(A != B);
		AssertCondition(B != A);

		AssertCondition(A < B);
		AssertCondition(!(B < A));

		AssertCondition(A <= B);
		AssertCondition(!(B <= A));

		AssertCondition(B > A);
		AssertCondition(!(A > B));

		AssertCondition(B >= A);
		AssertCondition(!(A >= B));
	}


	///
	/// Checks whether the comparison operators behave like a strict relation
	/// regarding two different elements A and B of type T, who are considered equal
	///
	template <typename T>
	static void AreComparisonOperatorsStrictForEqualElements(const T& A, const T& B)
	{
		AssertCondition(A == B);
		AssertCondition(B == A);

		AssertCondition(!(A != B));
		AssertCondition(!(B != A));

		AssertCondition(!(A < B));
		AssertCondition(!(B < A));

		AssertCondition(A <= B);
		AssertCondition(B <= A);

		AssertCondition(!(B > A));
		AssertCondition(!(A > B));

		AssertCondition(B >= A);
		AssertCondition(A >= B);
	}
};



///
/// Tests are packed as procedures
///
typedef void(*TEST_CASE_FUNCTION)();


class TestCollector;

TestCollector& GetGlobalTestCollector();


///
/// Stores information about a single test
///
class TestCase
{
private:
    /// Pointer to the test function
    TEST_CASE_FUNCTION m_pfnTestCase;

    /// Description of the test
    std::string m_Description;

public:
    
    ///
    /// Initializes a new test case and registers it
    /// with the test suite called Suite
    ///
    TestCase(TEST_CASE_FUNCTION pfnTestCase, const char* pDescription) :
        m_pfnTestCase(pfnTestCase),
        m_Description(pDescription)
    {
        // Nothing to do here
    }

    const char* GetDescription() const
    {
        return m_Description.c_str();
    }

    void Run() const
    {
        m_pfnTestCase();
    }
};



///
/// Defines and registers a test case
///
#define TEST_CASE(Suite, Name)                          \
    void Name();                                        \
    TestCaseRegistrator TestCaseObject__##Name(Suite, TestCase(Name, #Name));\
    void Name()



///
/// A collection of test cases
///
class TestSuite
{
private:
    /// A collection of all test cases registered within the class
    std::vector<TestCase> m_Tests;

    /// A short text, which describes this suite
    std::string m_Description;

public:
    TestSuite(const std::string& Description = "General") :
        m_Description(Description)
    {
        // Nothing to do here
    }

    void Add(TestCase const& test)
    {
        m_Tests.push_back(test);
    }

    void RunAll() const
    {
        std::cout
            << "\n========\n"
            << m_Description
            << "\n====\n\n";

		int failed = 0;

        for(std::size_t i = 0; i < m_Tests.size(); ++i)
        {
			std::cout << "   " << (i+1) << ". ";
			
			try
            {
                m_Tests[i].Run();
                std::cout << "[ OK     ] ";
            }
            catch (std::exception&)
            {
                std::cout << "[ Failed ] ";
				++failed;
            }

			std::cout << m_Tests[i].GetDescription() << std::endl;
        }

		size_t ok = m_Tests.size() - failed;

        std::cout
			<< "\n   Ran "
			<< m_Tests.size()
			<< " test(s), "
			<< ok
			<< " OK, "
			<< failed
			<< " failed ("
			<< (100 * static_cast<double>(ok) / m_Tests.size())
			<< "% success)\n\n";
    }

	///
	/// Finds the first test in the suite, whose descripion is pDescription
	///
	/// The function returns a pointer to the test case or NULL if
	/// no such test case can be found.
	///
	TestCase* FindFirst(const char* pDescription)
	{
		for (std::size_t i = 0; i < m_Tests.size(); ++i)
		{
			if (strcmp(m_Tests[i].GetDescription(), pDescription) == 0)
				return &m_Tests[i];
		}

		return NULL;
	}
};



///
/// A collection of test suites
///
class TestCollector
{
private:
    std::map<std::string, TestSuite> m_TestSuites;

public:
    void Add(std::string Suite, TestCase const & test)
    {
        std::map<std::string, TestSuite>::iterator it = m_TestSuites.find(Suite);

        if (it == m_TestSuites.end())
            it = m_TestSuites.insert(std::pair<std::string, TestSuite>(Suite, TestSuite(Suite))).first;

        (*it).second.Add(test);
    }


	///
	/// Runs all tests in all suites
	///
    void RunAll()
    {
        std::map<std::string, TestSuite>::iterator it;

        for (it = m_TestSuites.begin(); it != m_TestSuites.end(); ++it)
            (*it).second.RunAll();
    }


	///
	/// Runs the first case with description equal to pTestCaseName
	///
	/// The function searches all suites for a test called pTestCaseName
	/// If such a test case exists, the first one found will be ran.
	/// If no such test can be found, the function will execute no tests.
	///
	void Run(const char* pTestCaseName)
	{
		std::map<std::string, TestSuite>::iterator it = m_TestSuites.begin();
		TestCase* pc = NULL;

		for (; it != m_TestSuites.end(); ++it)
		{
			pc = (*it).second.FindFirst(pTestCaseName);
			
			if (pc)
				break;
		}

		if (pc)
		{
			try
			{
				pc->Run();
				std::cout << pc->GetDescription();
			}
			catch (std::exception&)
			{
				std::cout << "Failed!";
			}
		}

	}
};



///
/// Returns the global test collector
///
/// We use a function, instead of a global variable, in order to aviod the
/// so called "static initialization order fiasco":
/// http://www.parashift.com/c++-faq/static-init-order.html
///
/// Solution based on:
/// http://www.parashift.com/c++-faq/static-init-order-on-first-use.html
/// The difference is: we do not need to allocate memory dynamically,
/// since there is no problem freeing the static data, but only
/// during its initialization:
/// http://www.parashift.com/c++-faq/construct-on-first-use-v2.html
/// Additional information can be found here:
/// http://blogs.msdn.com/b/oldnewthing/archive/2004/03/08/85901.aspx
///
TestCollector& GetGlobalTestCollector()
{
    static TestCollector gtc;
    return gtc;
}



///
/// Registers individual tests with a test suite
///
class TestCaseRegistrator
{
public:
    TestCaseRegistrator(std::string Suite, TestCase const & test)
    {
        GetGlobalTestCollector().Add(Suite, test);
    }
};


int main(int argc, char* argv[])
{
#ifdef READ_TEST_CASE_NAME_FROM_STDIN

    char buffer[2000];
    std::cin.get(buffer, 2000);
    GetGlobalTestCollector().Run(buffer);

#else

    GetGlobalTestCollector().RunAll();

#endif

    return 0;
}
