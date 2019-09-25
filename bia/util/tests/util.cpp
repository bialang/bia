#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <util/finally.hpp>
#include <util/type_traits.hpp>

using namespace bia::util;

TEST_CASE("scope guard 'finally'", "[util]")
{
	auto x = true;

	SECTION("without cancel")
	{
		{
			finally f([&] { x = false; });
		}

		REQUIRE_FALSE(x);
	}

	SECTION("with cancel")
	{
		{
			finally f([&] { x = false; });

			f.cancel();
		}

		REQUIRE(x);
	}
}

TEST_CASE("conjunction", "[type_traits]")
{
	REQUIRE(conjunction<>::value == true);
	REQUIRE(conjunction<true>::value == true);
	REQUIRE(conjunction<false>::value == false);
	REQUIRE(conjunction<true, true, true, true>::value == true);
	REQUIRE(conjunction<true, true, false, true>::value == false);
}