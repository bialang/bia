#include "test.hpp"
#include "testFunctions.hpp"

#include <memory>
#include <string>
#include <biaMachineContext.hpp>
#include <biaClassRaw.hpp>

using namespace bia;
using namespace bia::framework::native;
using namespace bia::framework::object;


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
		bia::machine::BiaMachineContext context(std::shared_ptr<bia::machine::BiaAllocator>(new bia::machine::BiaAllocator()));
		
		if (argc > 1)
		{
			if (!std::strcmp(argv[1], "math_expression"))
			{
				auto szScript = R"(
global a = 652
global b = 6956
global c = 998
global d = 53
global result_const = 652 - 2 + 6956 * 998 / 53
global result_mixed = a - 2 + b * c / d
)";

				context.Execute(szScript, std::char_traits<char>::length(szScript));

				TestValue(context, "result_const", 652 - 2 + 6956 * 998 / 53);
				TestValue(context, "result_mixed", 652 - 2 + 6956 * 998 / 53);
			}
			else if (!std::strcmp(argv[1], "execute"))
			{
				auto szScript = R"(
print foo1()
print "Hello, World"
)";

				context.SetFunction("foo1", &foo1);

				context.SetScript("test", szScript, std::char_traits<char>::length(szScript));
				context.ExecuteScript("test");
			}
			else if (!std::strcmp(argv[1], "passing_order"))
			{
				auto szScript = R"(
global a = "a"
global b = "b"
global c = "c"

# Static function order
static_order1(a, b)
static_order1("a", b)
static_order2(a, b, c)
static_order2(a, "b", c)
static_order2("a", b, "c")

# Member function order
member_order1(a, b)
member_order1("a", b)
member_order2(a, b, c)
member_order2(a, "b", c)
member_order2("a", b, "c")
)";

				context.SetFunction("static_order1", &static_order1);
				context.SetFunction("static_order2", &static_order2);
				context.SetLambda("member_order1", [] (const char * a, const char * b) {
					BIA_ASSERT(std::strcmp(a, "a") == 0, "Strings don't match");
					BIA_ASSERT(std::strcmp(b, "b") == 0, "Strings don't match");
				});
				context.SetLambda("member_order2", [] (const char * a, const char * b, const char * c) {
					BIA_ASSERT(std::strcmp(a, "a") == 0, "Strings don't match");
					BIA_ASSERT(std::strcmp(b, "b") == 0, "Strings don't match");
					BIA_ASSERT(std::strcmp(c, "c") == 0, "Strings don't match");
				});

				context.Execute(szScript, std::char_traits<char>::length(szScript));
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
			else if (!std::strcmp(argv[1], "type_cast"))
			{
				//Integral test
				TestValue(BiaInt(0), 0);
				TestValue(BiaInt(0x6100), 0x6100);
				TestValue(BiaInt(~0ll), ~0ll);
				TestValue(BiaInt(-1), -1);
				TestValue(BiaInt(0x6100), true);

				//Float test
				TestValue(BiaFloat(0.0f), 0.0f);
				TestValue(BiaFloat(-0.0f), -0.0f);
				TestValue(BiaFloat(1.01f), 1.01f);
				TestValue(BiaFloat(65825.987f), 65825.987f);
				TestValue(BiaFloat(0.05f), true);

				//Double test
				TestValue(BiaDouble(0.0), 0.0);
				TestValue(BiaDouble(-0.0), -0.0);
				TestValue(BiaDouble(1.01), 1.01);
				TestValue(BiaDouble(65825.987), 65825.987);
				TestValue(BiaDouble(0.05), true);

				//C-String test
				TestValue(BiaCString(""), "");
				TestValue(BiaCString("hi"), "hi");

				//Custom
				TestValue(BiaClassRaw<std::string>(std::make_shared<std::string>("hello")), std::string("hello"));
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