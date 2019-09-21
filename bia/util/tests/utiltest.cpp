#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include <util/finally.hpp>


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