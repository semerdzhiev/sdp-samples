#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Box/Box.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

BEGIN_TEST_MODULE_ATTRIBUTE()
	TEST_MODULE_ATTRIBUTE(L"Project", L"UnitTests")
	TEST_MODULE_ATTRIBUTE(L"Date", L"17/10/2015")
END_TEST_MODULE_ATTRIBUTE()

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage("Entered ModuleInitialize");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	Logger::WriteMessage("Entering ModuleCleanup");
}


namespace UnitTestVisualCpp
{		
	TEST_CLASS(BoxTest)
	{
	public:

		BoxTest()
		{
			Logger::WriteMessage("Entering BoxTest::BoxTest()");
		}

		~BoxTest()
		{
			Logger::WriteMessage("Entering BoxTest::~BoxTest()");
		}

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("Entering ClassInitialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("Entering ClassCleanup");
		}

		TEST_METHOD(CreateEmptyBox)
		{
			Box obj;
		}

		TEST_METHOD(CreateBox)
		{
			Box obj(10);
		}

		TEST_METHOD(CreateBoxArray)
		{
			Box* p = new Box[1000000];
			delete[] p;
		}

		TEST_METHOD(StoreAndRetrieveValue)
		{
			Box obj;

			obj.Add(10.0);

			Assert::AreEqual(obj.Peek(), 10.0);
		}

		TEST_METHOD(StoreAndModifyValue)
		{
			Box obj;

			obj.Add(10);
			obj.Add(20);

			Assert::AreEqual(obj.Peek(), 20.0);
		}

		TEST_METHOD(IsEmpty)
		{
			Box obj;

			Assert::IsTrue(obj.IsEmpty());
		}


		void Test_NotEmpty()
		{
			Box obj;
			obj.Add(10);

			Assert::IsFalse(obj.IsEmpty());
		}

		TEST_METHOD(PeekOnEmptyBox)
		{
			Box obj;

			try
			{
				obj.Peek();

				// The line above should throw, so if we reach this,
				// the test has failed.
				Assert::Fail(L"Exception not thrown");
			}
			catch (std::exception &)
			{
				// OK, std::exception thrown
			}
			catch (...)
			{
				// The exception should be of type std::exception,
				// so if we reach this clause, the test has failed.
				Assert::Fail(L"Wrong exception type thrown");
			}
		}

		TEST_METHOD(PeekOnEmptyBox2)
		{
			Box obj;

			Assert::ExpectException<std::exception>(
				[&obj]()
				{
					obj.Peek();
				}
			);
		}

	};
}