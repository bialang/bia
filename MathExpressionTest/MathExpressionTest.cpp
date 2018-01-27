#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MathExpressionTest
{		
	TEST_CLASS(MathExpressionTest)
	{
	public:
		
		TEST_METHOD(TestDotFirst)
		{
			Assert::AreEqual(3 + 4, 7);
		}

	};
}