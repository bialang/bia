#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <bia/string/encoding/unicode.hpp>
#include <catch.hpp>

using namespace bia::string::encoding;

TEST_CASE("standard unicode", "[string][encoding][benchmark]")
{
	BENCHMARK("category of: a")
	{
		return category_of('a');
	};

	BENCHMARK("category of: 0x1a4a")
	{
		return category_of(0x1a4a);
	};

	BENCHMARK("category of: 0x257e")
	{
		return category_of(0x257e);
	};

	BENCHMARK("category of: 0x10850")
	{
		return category_of(0x10850);
	};

	BENCHMARK("category of: 0x1d697")
	{
		return category_of(0x1d697);
	};

	BENCHMARK("category of: 0x10ffff")
	{
		return category_of(0x10ffff);
	};

	REQUIRE(category_of('a') == Category::Ll);
	REQUIRE(category_of('A') == Category::Lu);
}
