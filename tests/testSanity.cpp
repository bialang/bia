#include <biaMachineContext.hpp>

#include "test.hpp"
#include "testFunctions.hpp"

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
	try
	{
		if (argc > 1)
		{
			bia::machine::BiaMachineContext context(std::shared_ptr<bia::machine::BiaAllocator>(new bia::machine::BiaAllocator()));

			if (!std::strcmp(argv[1], "math_const"))
			{
				auto szScript = "global result = 652 - 2 + 6956 * 998 / 53";

				context.Execute(szScript, std::char_traits<char>::length(szScript));

				TestValue(context, "result", 652 - 2 + 6956 * 998 / 53);
			}
			else if (!std::strcmp(argv[1], "math_mixed"))
			{
				auto szScript = R"(
global a = 652
global b = 6956
global c = 998
global d = 53
global result = a - 2 + b * c / d
)";

				context.Execute(szScript, std::char_traits<char>::length(szScript));

				TestValue(context, "result", 652 - 2 + 6956 * 998 / 53);
			}
			else if (!std::strcmp(argv[1], "static_function"))
			{
				auto szScript = R"(
global a = foo1()
global b = foo2("hi")
global c = foo3(-43, -57)
global d = foo4()(43, 57)
)";

				context.SetFunction("foo1", &foo1);
				context.SetFunction("foo2", &foo2);
				context.SetFunction("foo3", &foo3);
				context.SetFunction("foo4", &foo4);

				context.Execute(szScript, std::char_traits<char>::length(szScript));

				//Test results
				TestValue(context, "a", 61);
				TestValue(context, "b", -61);
				TestValue(context, "c", -100);
				TestValue(context, "d", 100);
			}
		}
	}
	catch (const char * e)
	{
		printf("%s: %s\n", typeid(e).name(), e);
		
		return TEST_ERRORS;
	}
	catch (const std::exception & e)
	{
		printf("%s: %s\n", typeid(e).name(), e.what());

		return TEST_ERRORS;
	}
	catch (const bia::exception::Exception & e)
	{
		e.Print();

		return TEST_ERRORS;
	}
	catch (...)
	{
		puts("Something has been thrown.");

		return TEST_ERRORS;
	}

	return 0;
}