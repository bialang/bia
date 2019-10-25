#define CATCH_CONFIG_MAIN

#include <bytecode/writer.hpp>
#include <catch.hpp>
#include <stream/buffer_output_stream.hpp>

using namespace bia;
using namespace bia::bytecode;

TEST_CASE("instruction writer", "[bytecode]")
{
	stream::buffer_output_stream output;
	instruction_writer wi(output);

	SECTION("OC_RETURN")
	{
		wi.write_instruction<OC_RETURN>();
	}

	SECTION("immediate ints")
	{
	}
}