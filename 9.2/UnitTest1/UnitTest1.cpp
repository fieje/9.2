#include "pch.h"
#include "CppUnitTest.h"
#include "../9.2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestBinarySearchStudent)
		{
			const int N = 3;
			Student students[N] = {
				{ "Smith", 2, COMPUTER_SCIENCE, 80, 85, 90 },
				{ "Johnson", 3, INFORMATICS, 75, 90, 85 },
				{ "Williams", 1, MATH_AND_ECONOMICS, 85, 80, 75 }
			};

			bool found = BinarySearchStudent(students, N, "Johnson", 3, INFORMATICS);
			bool notFound = BinarySearchStudent(students, N, "Brown", 2, COMPUTER_SCIENCE);

			Assert::IsTrue(found);
			Assert::IsFalse(notFound);
		}
	};
}
