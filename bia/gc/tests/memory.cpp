#include <catch.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <gc/memory/space.hpp>

using namespace bia::gc::memory;

TEST_CASE("space", "[gc]")
{
	space sp(std::make_shared<simple_allocator>(), 32);

	REQUIRE(sp.size() == 0);

	SECTION("simple writes")
	{
		auto buf = sp.next_region(16).get();

		REQUIRE(buf.size() == 16);

		// one byte should be on the next page
		buf = sp.next_region(17).get();

		REQUIRE(buf.size() == 16);
		REQUIRE(sp.size() == 32);
	}
}