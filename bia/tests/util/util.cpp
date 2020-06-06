#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <util/finally.hpp>
#include <util/type_traits/conjunction.hpp>
#include <util/type_traits/equals_any.hpp>
#include <util/type_traits/size_of.hpp>
#include <util/type_traits/type_index.hpp>

using namespace bia::util;
using namespace bia::util::type_traits;

TEST_CASE("scope guard 'finally'", "[util]")
{
	auto x = true;

	SECTION("without cancel")
	{
		{
			auto f = make_finally([&] { x = false; });
		}

		REQUIRE_FALSE(x);
	}

	SECTION("with cancel")
	{
		{
			auto f = make_finally([&] { x = false; });

			f.cancel();
		}

		REQUIRE(x);
	}
}

TEST_CASE("conjunction", "[type_traits][util]")
{
	REQUIRE(conjunction<>::value == false);
	REQUIRE(conjunction<true>::value == true);
	REQUIRE(conjunction<false>::value == false);
	REQUIRE(conjunction<true, true, true, true>::value == true);
	REQUIRE(conjunction<true, true, false, true>::value == false);
}

TEST_CASE("size_of", "[type_traits][util]")
{
	REQUIRE(size_of<>::value == 0);
	REQUIRE(size_of<int>::value == sizeof(int));
	REQUIRE(size_of<int, float, double>::value == sizeof(int) + sizeof(float) + sizeof(double));
}

TEST_CASE("equals_any", "[type_traits][util]")
{
	REQUIRE(!equals_any<int, 0, 1, 2>::value);
	REQUIRE(equals_any<int, 0, 1, 2, 3, 0>::value);
	REQUIRE(equals_any<int, 0, 1, 2, 3, 0, 2, 6>::value);

	REQUIRE(!equals_any_type<void, int, float>::value);
	REQUIRE(equals_any_type<void, int, float, void>::value);
	REQUIRE(equals_any_type<void, int, float, void, int>::value);
}

TEST_CASE("type_index", "[type_traits][util]")
{
	REQUIRE(type_index<int, int>::value == 0);
	REQUIRE(type_index<int, int, float>::value == 0);
	REQUIRE(type_index<int, float, int>::value == 1);
	REQUIRE(type_index<int, float, int, double>::value == 1);
	REQUIRE(type_index<int, float, double, int, int>::value == 2);
	REQUIRE((type_index<int, float, double, short, char>::value == type_index<>::npos));
}
