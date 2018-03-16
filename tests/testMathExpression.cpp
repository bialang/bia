#include <biaMachineContext.hpp>

enum
{
	UPDATE_ERRORS = 0x01,
	CONFIGURE_ERRORS = 0x02,
	BUILD_ERRORS = 0x04,
	TEST_ERRORS = 0x08,
	MEMORY_ERRORS = 0x10,
	COVERAGE_ERRORS = 0x20,
	SUBMIT_ERRORS = 0x40
};

int main(int argc, char ** argv)
{
	if (argc > 1)
	{
		bia::machine::BiaMachineContext context(std::shared_ptr<bia::machine::BiaAllocator>(new bia::machine::BiaAllocator()));

		if (!std::strcmp(argv[1], "constant"))
		{
			auto szScript = "global test_dot_first_constant = 652 - 2 + 6956 * 998 / 53";

			context.Run(szScript, std::char_traits<char>::length(szScript));

			//Get variable
			auto pVariable = context.GetGlobal("test_dot_first_constant");

			if (!pVariable)
				return BUILD_ERRORS;

			//Get value
			auto pValue = pVariable->Cast<int>();

			//Assert::IsNotNull(pValue, L"Invalid type.");
			if (!pValue)
				return BUILD_ERRORS;

			//Test value
			if (*pValue != 652 - 2 + 6956 * 998 / 53)
				return TEST_ERRORS;
		}
		else if (!std::strcmp(argv[1], "mixed"))
		{
			auto szScript = R"(
global a = 652
global b = 6956
global c = 998
global d = 53
global test_dot_first_mixed = a - 2 + b * c / d
)";

			context.Run(szScript, std::char_traits<char>::length(szScript));

			//Get variable
			auto pVariable = context.GetGlobal("test_dot_first_mixed");

			if (!pVariable)
				return BUILD_ERRORS;

			//Get value
			auto pValue = pVariable->Cast<int>();

			//Assert::IsNotNull(pValue, L"Invalid type.");
			if (!pValue)
				return BUILD_ERRORS;

			//Test value
			if (*pValue != 652 - 2 + 6956 * 998 / 53)
				return TEST_ERRORS;
		}
	}

	return 0;
}