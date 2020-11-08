#include <bia/util/variant.hpp>
#include <catch.hpp>

using namespace bia::util;

template<typename T>
struct tester
{
	T value;
	static int count;

	tester(T value) : value{ value }
	{
		++count;
	}
	tester(const tester& copy) : tester(copy.value)
	{}
	tester(tester&& move) : tester(move.value)
	{
		move.value = {};
	}
	~tester()
	{
		--count;
	}
};

template<typename T>
int tester<T>::count = 0;

TEST_CASE("variant setting", "[util]")
{
	REQUIRE(tester<int>::count == 0);
	REQUIRE(tester<char>::count == 0);

	{
		variant<tester<int>, tester<char>> v;

		v.emplace<tester<int>>(5);

		REQUIRE(tester<int>::count == 1);
		REQUIRE(tester<char>::count == 0);

		REQUIRE(v.get<0>().value == 5);
		REQUIRE(v.get<tester<int>>().value == 5);
		REQUIRE_THROWS_AS(v.get<1>(), bia::error::exception);
		REQUIRE_THROWS_AS(v.get<tester<char>>(), bia::error::exception);

		SECTION("overwrite")
		{
			v.emplace<tester<char>>('b');

			REQUIRE(tester<int>::count == 0);
			REQUIRE(tester<char>::count == 1);

			REQUIRE(v.get<1>().value == 'b');
			REQUIRE(v.get<tester<char>>().value == 'b');
			REQUIRE_THROWS_AS(v.get<0>(), bia::error::exception);
			REQUIRE_THROWS_AS(v.get<tester<int>>(), bia::error::exception);
		}

		SECTION("destroy")
		{
			v.destroy();

			REQUIRE(tester<int>::count == 0);
			REQUIRE(tester<char>::count == 0);
		}
	}

	REQUIRE(tester<int>::count == 0);
	REQUIRE(tester<char>::count == 0);
}

TEST_CASE("variant construction", "[util]")
{
	REQUIRE(tester<int>::count == 0);
	REQUIRE(tester<char>::count == 0);

	typedef variant<tester<int>, tester<char>> v_type;

	{
		v_type v;

		v.emplace<tester<char>>('b');

		REQUIRE(tester<int>::count == 0);
		REQUIRE(tester<char>::count == 1);
		REQUIRE(v.get<1>().value == 'b');
		REQUIRE(v.get<tester<char>>().value == 'b');
		REQUIRE_THROWS_AS(v.get<0>(), bia::error::exception);
		REQUIRE_THROWS_AS(v.get<tester<int>>(), bia::error::exception);

		SECTION("copy")
		{
			v_type copy{ v };

			REQUIRE(tester<int>::count == 0);
			REQUIRE(tester<char>::count == 2);
			REQUIRE(copy.get<1>().value == 'b');
			REQUIRE(copy.get<tester<char>>().value == 'b');
			REQUIRE_THROWS_AS(copy.get<0>(), bia::error::exception);
			REQUIRE_THROWS_AS(copy.get<tester<int>>(), bia::error::exception);

			REQUIRE(v.get<1>().value == 'b');
			REQUIRE(v.get<tester<char>>().value == 'b');
			REQUIRE_THROWS_AS(v.get<0>(), bia::error::exception);
			REQUIRE_THROWS_AS(v.get<tester<int>>(), bia::error::exception);
		}

		SECTION("move")
		{
			v_type move{ std::move(v) };

			REQUIRE(tester<int>::count == 0);
			REQUIRE(tester<char>::count == 1);
			REQUIRE(move.get<1>().value == 'b');
			REQUIRE(move.get<tester<char>>().value == 'b');
			REQUIRE_THROWS_AS(move.get<0>(), bia::error::exception);
			REQUIRE_THROWS_AS(move.get<tester<int>>(), bia::error::exception);

			REQUIRE_THROWS_AS(v.get<1>(), bia::error::exception);
			REQUIRE_THROWS_AS(v.get<tester<char>>(), bia::error::exception);
			REQUIRE_THROWS_AS(v.get<0>(), bia::error::exception);
			REQUIRE_THROWS_AS(v.get<tester<int>>(), bia::error::exception);
		}
	}

	REQUIRE(tester<int>::count == 0);
	REQUIRE(tester<char>::count == 0);
}
