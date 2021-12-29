#include <bia/util/portable/stream.hpp>
#include <catch2/catch.hpp>
#include <cstdint>
#include <sstream>

using namespace bia::util;

constexpr std::uint8_t b = 'b';
constexpr auto ia        = static_cast<std::uint16_t>('i' | 'a' << 8);
constexpr auto lang      = static_cast<std::uint32_t>('l' | 'a' << 8 | 'n' << 16 | 'g' << 24);

TEST_CASE("portable writing", "[util][portable]")
{
	std::stringstream ss;

	portable::write(ss, b, ia, lang);

	REQUIRE(ss.str() == "bialang");
}

TEST_CASE("portable reading", "[util][portable]")
{
	std::stringstream ss("bialang");

	REQUIRE(portable::read<std::uint8_t>(ss) == b);
	REQUIRE(portable::read<std::uint16_t>(ss) == ia);
	REQUIRE(portable::read<std::uint32_t>(ss) == lang);
}
