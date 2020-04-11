#define CATCH_CONFIG_MAIN

#include <bytecode/writer/common.hpp>
#include <bytecode/writer/member.hpp>
#include <catch.hpp>
#include <sstream>
#include <utility>

using namespace bia::bytecode;
using namespace bia::bytecode::writer;

template<bool Optimize, typename T>
inline std::size_t optimized_test_write(T&& value)
{
	std::stringstream s;

	optimized_write<Optimize>(s, std::forward<T>(value));

	return s.str().length();
}

TEST_CASE("instruction writer", "[bytecode]")
{
	/*stream::buffer_output_stream output;
	instruction_writer wi(output);

	SECTION("OC_RETURN")
	{
	//
	    wi.write_instruction<OC_RETURN>();
	}

	SECTION("immediate ints")
	{
	}*/
}

TEST_CASE("common writer", "[bytecode]")
{
	SECTION("unoptimized")
	{
		REQUIRE(optimized_test_write<false>(std::int8_t{ 0 }) == 1);
		REQUIRE(optimized_test_write<false>(std::int16_t{ -128 }) == 2);
		REQUIRE(optimized_test_write<false>(std::int32_t{ -56 }) == 4);
		REQUIRE(optimized_test_write<false>(std::int64_t{ 65 }) == 8);
	}

	SECTION("optimized")
	{
		REQUIRE(optimized_test_write<true>(std::int8_t{ 0 }) == 1);
		REQUIRE(optimized_test_write<true>(std::int16_t{ -128 }) == 1);
		REQUIRE(optimized_test_write<true>(std::int32_t{ 127 }) == 1);
		REQUIRE(optimized_test_write<true>(std::int64_t{ -45 }) == 1);
		REQUIRE(optimized_test_write<true>(std::int16_t{ 8665 }) == 2);
		REQUIRE(optimized_test_write<true>(std::int32_t{ 5464 }) == 2);
		REQUIRE(optimized_test_write<true>(std::int64_t{ -9646 }) == 2);
		REQUIRE(optimized_test_write<true>(std::int32_t{ 546342344 }) == 4);
		REQUIRE(optimized_test_write<true>(std::int64_t{ -546343344 }) == 4);
		REQUIRE(optimized_test_write<true>(std::int64_t{ 995656894948946565 }) == 8);
	}
}

TEST_CASE("member writer", "[bytecode]")
{
	SECTION("unoptimized")
	{
		REQUIRE(member_index<false>(member::tos{}) == mo_tos);
		REQUIRE(member_index<false>(member::args{ 255 }) == mo_args);
		REQUIRE(member_index<false>(member::global{ 25 }) == mo_global_16);
		REQUIRE(member_index<false>(member::global{ 6531 }) == mo_global_16);
		REQUIRE(member_index<false>(member::local{ 25 }) == mo_local_16);
		REQUIRE(member_index<false>(member::local{ 6531 }) == mo_local_16);
		REQUIRE(member_index<false>(member::resource{ 25 }) == mo_resource_16);
		REQUIRE(member_index<false>(member::resource{ 6531 }) == mo_resource_16);
	}

	SECTION("optimized")
	{
		REQUIRE(member_index<true>(member::tos{}) == mo_tos);
		REQUIRE(member_index<true>(member::args{ 255 }) == mo_args);
		REQUIRE(member_index<true>(member::global{ 25 }) == mo_global_8);
		REQUIRE(member_index<true>(member::global{ 6531 }) == mo_global_16);
		REQUIRE(member_index<true>(member::local{ 25 }) == mo_local_8);
		REQUIRE(member_index<true>(member::local{ 6531 }) == mo_local_16);
		REQUIRE(member_index<true>(member::resource{ 25 }) == mo_resource_8);
		REQUIRE(member_index<true>(member::resource{ 6531 }) == mo_resource_16);
	}
}
