#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <member/native/integer.hpp>
#include <member/cast.hpp>
#include <limits>
#include <cmath>

using namespace bia::member;

template<typename Float>
inline bool equal(Float left, Float right)
{
	return std::abs(left - right) < std::numeric_limits<Float>::epsilon();
}

TEST_CASE("numerical casting", "[member]")
{
	native::integer m{ 34 };
	
	REQUIRE(cast<member::int_type>(m) == 34);
	REQUIRE(cast<int>(m) == 34);
	REQUIRE(cast<char>(m) == 34);
	REQUIRE(equal(cast<double>(m), 34.0));
	REQUIRE(equal(cast<float>(m), 34.0f));
	//REQUIRE(*cast<const member::int_type*>(m) == 34);
	//REQUIRE_THROWS(*cast<member::int_type*>(m) == 34);
	//REQUIRE(*cast<member::int_type&>(m) == 34);
}