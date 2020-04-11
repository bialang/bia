#define CATCH_CONFIG_MAIN

#include <bytecode/writer/member.hpp>
#include <catch.hpp>

using namespace bia::bytecode;
using namespace bia::bytecode::writer;

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
