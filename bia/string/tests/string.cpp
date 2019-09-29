#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <string/string.hpp>

using namespace bia::string;

TEST_CASE("static string", "[string]")
{
	constexpr char16_t str[] = u"hello darkness";

	auto tmp = string::from_static_buffer(str, 0);

	REQUIRE(tmp.length() == sizeof(str) / sizeof(char16_t) - 1);
	REQUIRE(tmp.buffer() == str);
}