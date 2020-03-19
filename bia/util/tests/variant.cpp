#include <catch.hpp>
#include <util/variant.hpp>

using namespace bia::util;

template<typename T>
struct tester
{
	T value;
	static int count;

	tester(T value) : value(value)
	{
		++count;
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
		REQUIRE_THROWS_AS(v.get<1>(), bia::exception::bad_variant_access);

		SECTION("overwrite")
		{
			v.emplace<tester<char>>('b');

			REQUIRE(tester<int>::count == 0);
			REQUIRE(tester<char>::count == 1);

			REQUIRE(v.get<1>().value == 'b');
			REQUIRE_THROWS_AS(v.get<0>(), bia::exception::bad_variant_access);
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
