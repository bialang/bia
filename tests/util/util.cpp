#define CATCH_CONFIG_MAIN

#include <bia/util/finally.hpp>
#include <bia/util/type_traits/conjunction.hpp>
#include <bia/util/type_traits/equals_any.hpp>
#include <bia/util/type_traits/int_maker.hpp>
#include <bia/util/type_traits/invokable_info.hpp>
#include <bia/util/type_traits/is_invokable.hpp>
#include <bia/util/type_traits/is_varargs_invokable.hpp>
#include <bia/util/type_traits/multi_comparable.hpp>
#include <bia/util/type_traits/size_of.hpp>
#include <bia/util/type_traits/type_index.hpp>
#include <bia/util/type_traits/type_select.hpp>
#include <catch2/catch.hpp>

using namespace bia::util;
using namespace bia::util::type_traits;

TEST_CASE("scope guard 'finally'", "[util]")
{
	auto x = true;

	SECTION("without cancel")
	{
		{
			auto f = finallay([&] { x = false; });
		}

		REQUIRE_FALSE(x);
	}

	SECTION("with cancel")
	{
		{
			auto f = finallay([&] { x = false; });

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
	REQUIRE((type_index<int, float, double, short, char>::value == npos));
}

TEST_CASE("Type_select", "[type_traits][util]")
{
	REQUIRE(std::is_same<decltype(Type_select<0, 1, int, double>::selected), const Type_container<int>>::value);
	REQUIRE(std::is_same<decltype(Type_select<1, 2, int, double, float, void>::selected), const Type_container<double, float>>::value);
	REQUIRE(std::is_same<decltype(Type_select<2, 2, int, double, float, void>::selected), const Type_container<float, void>>::value);
}

TEST_CASE("is_invokable", "[type_traits][util]")
{
	REQUIRE(Is_invokable<void (*)()>::value);
	REQUIRE(!Is_invokable<void (*)(bool)>::value);
	REQUIRE(!Is_invokable<void (*)(bool), std::string>::value);
	REQUIRE(Is_invokable<void (*)(int), int>::value);
	REQUIRE(Is_invokable<void (*)(int), bool>::value);
}

TEST_CASE("Is_vararg_invokable", "[type_traits][util]")
{
	using namespace bia::member::function;
	REQUIRE(!Is_varargs_invokable<void (*)()>::value);
	REQUIRE(!Is_varargs_invokable<void (*)(int)>::value);
	REQUIRE(!Is_varargs_invokable<void (*)(Varargs<int>, int)>::value);
	REQUIRE(!Is_varargs_invokable<void (*)(Varargs<int>, int, Varargs<int>)>::value);
	REQUIRE(Is_varargs_invokable<void (*)(float, int, Varargs<int>)>::value);
}

TEST_CASE("Multi_comparable", "[type_traits][util]")
{
	REQUIRE(std::is_same<decltype(Multi_equal_comparable<int, double>::indices),
	                     const Int_container<std::size_t, 0>>::value);
}

TEST_CASE("int maker", "[type_traits][util]")
{
	REQUIRE(std::is_same<const Int_container<int, 0, 1, 2>, decltype(Int_sequencer<int, 0, 3>::value)>::value);
	REQUIRE(
	  std::is_same<const Int_container<int, 1, 2, 3, 4, 5>, decltype(Int_sequencer<int, 1, 6>::value)>::value);
	REQUIRE(
	  !std::is_same<const Int_container<int, 1, 2, 3, 4, 5>, decltype(Int_sequencer<int, 0, 6>::value)>::value);
}

void foo1();
int foo2(int);
double foo3(char, int);

TEST_CASE("function info", "[type_traits][util]")
{
	REQUIRE((Invokable_info<decltype(foo1)>::is_invokable && !Invokable_info<decltype(foo1)>::is_method &&
	         !Invokable_info<decltype(foo1)>::is_const && Invokable_info<decltype(foo1)>::argument_count == 0));
	REQUIRE((Invokable_info<decltype(foo2)>::is_invokable && !Invokable_info<decltype(foo2)>::is_method &&
	         !Invokable_info<decltype(foo2)>::is_const && Invokable_info<decltype(foo2)>::argument_count == 1));
	REQUIRE((Invokable_info<decltype(foo3)>::is_invokable && !Invokable_info<decltype(foo3)>::is_method &&
	         !Invokable_info<decltype(foo3)>::is_const && Invokable_info<decltype(foo3)>::argument_count == 2));
	REQUIRE(std::is_void<typename Invokable_info<decltype(foo1)>::Return>::value);
	REQUIRE(std::is_same<typename Invokable_info<decltype(foo2)>::Return, int>::value);
	REQUIRE(std::is_same<typename Invokable_info<decltype(foo3)>::Return, double>::value);
}
