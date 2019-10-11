#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <util/cstring_iterator.hpp>
#include <util/finally.hpp>
#include <util/iterator_equals.hpp>
#include <util/type_traits/conjunction.hpp>
#include <util/type_traits/equals_any.hpp>
#include <util/type_traits/size_of.hpp>

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

TEST_CASE("iterator_equals", "[util]")
{
	auto str0	 = u"hello world";
	auto end_str0 = str0 + std::char_traits<char16_t>::length(str0);
	auto str1	 = "hello world";
	auto end_str1 = str1 + std::char_traits<char>::length(str1);
	auto str2	 = "hello";
	auto end_str2 = str2 + std::char_traits<char>::length(str2);
	auto str3	 = U"qwe";
	auto end_str3 = str3 + std::char_traits<char32_t>::length(str3);
	auto str4	 = "hello world!";
	auto end_str4 = str4 + std::char_traits<char>::length(str4);

	/*SECTION("only one")
	{
		auto result = iterator_equals(str0, end_str0, str1, end_str1);

		REQUIRE(result == 0);

		result = iterator_equals(str0, end_str0, str2, end_str2);

		REQUIRE(result == 1);

		result = iterator_equals(str0, end_str0, str4, end_str4);

		REQUIRE(result == 1);
	}

	SECTION("multiple")
	{
		auto result = iterator_equals(str0, end_str0, str2, end_str2, str4, end_str4, str3, end_str3, str1, end_str1);

		REQUIRE(result == 3);
	}*/
}

TEST_CASE("iterator_starts_with", "[util]")
{
	auto str0 = u"hello world";
	auto str1 = "hello world";
	auto str2 = "hello";
	auto str3 = U"qwe";
	auto str4 = "hello world!";

	SECTION("only one")
	{
		auto result = iterator_starts_with(cstring_iterator<char16_t>(str0), cstring_iterator<char>(str1)).first;

		REQUIRE(result == 0);

		result = iterator_starts_with(cstring_iterator<char16_t>(str0), cstring_iterator<char>(str2)).first;

		REQUIRE(result == 0);

		result = iterator_starts_with(cstring_iterator<char16_t>(str0), cstring_iterator<char32_t>(str3)).first;

		REQUIRE(result == 1);

		result = iterator_starts_with(cstring_iterator<char16_t>(str0), cstring_iterator<char>(str4)).first;

		REQUIRE(result == 1);
	}

	SECTION("multiple")
	{
		auto result = iterator_starts_with(cstring_iterator<char16_t>(str0), cstring_iterator<char32_t>(str3),
										   cstring_iterator<char>(str4), cstring_iterator<char>(str1))
						  .first;

		REQUIRE(result == 2);

		result = iterator_starts_with(cstring_iterator<char16_t>(str0), cstring_iterator<char32_t>(str3),
									  cstring_iterator<char>(str4), cstring_iterator<char>(str1),
									  cstring_iterator<char>(str2))
					 .first;

		REQUIRE(result == 2);
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
	REQUIRE(equals_any<int, 0>::value == false);
	REQUIRE(equals_any<int, 0, 1, 2>::value == false);
	REQUIRE(equals_any<int, 0, 1, 2, 3, 0>::value == true);
	REQUIRE(equals_any<int, 0, 1, 2, 3, 0, 2, 6>::value == true);

	REQUIRE(equals_any_type<void>::value == false);
	REQUIRE(equals_any_type<void, int, float>::value == false);
	REQUIRE(equals_any_type<void, int, float, void>::value == true);
	REQUIRE(equals_any_type<void, int, float, void, int>::value == true);
}