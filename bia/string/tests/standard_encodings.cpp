#include <catch.hpp>
#include <string/encoding/standard/ascii.hpp>

using namespace bia::string::encoding;
using namespace bia::string::encoding::standard;

TEST_CASE("standard ascii encoder", "[string][encoder]")
{
	std::int8_t buffer[] = { 'H', 'e', 'l', 'l', 'o', '!', 0 };
	auto str = encoder::convert(encoder::get_instance(encoder::STANDARD_ENCODING::ASCII), buffer, sizeof(buffer));

	SECTION("correct encoding")
	{}

	SECTION("invalid character")
	{}
}