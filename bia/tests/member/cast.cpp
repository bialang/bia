#define CATCH_CONFIG_MAIN

#include <bia/member/cast/cast.hpp>
#include <bia/member/native/integer.hpp>
#include <catch.hpp>
#include <cmath>
#include <limits>

using namespace bia::member;

template<typename Float>
inline bool equal(Float left, Float right)
{
	return std::abs(left - right) < std::numeric_limits<Float>::epsilon();
}

TEST_CASE("numerical casting", "[member]")
{
	native::integer m{ 34 };

	REQUIRE(cast::cast<member::int_type>(m) == 34);
	REQUIRE(cast::cast<int>(m) == 34);
	REQUIRE(cast::cast<char>(m) == 34);
	REQUIRE(equal(cast::cast<double>(m), 34.0));
	REQUIRE(equal(cast::cast<float>(m), 34.0f));
	// REQUIRE(*cast<const member::int_type*>(m) == 34);
	// REQUIRE_THROWS(*cast<member::int_type*>(m) == 34);
	// REQUIRE(*cast<member::int_type&>(m) == 34);
}
