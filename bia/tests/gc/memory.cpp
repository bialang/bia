#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/gc/memory/space.hpp>
#include <catch.hpp>

using namespace bia::gc::memory;

TEST_CASE("space", "[gc]")
{
	int count = 0;

	{
		space sp(std::make_shared<simple_allocator>(
		             [&count](std::size_t s) {
			             ++count;

			             auto ptr = std::malloc(s);

			             return ptr;
		             },
		             [&count](void* ptr) {
			             if (ptr) {
				             --count;

				             std::free(ptr);
			             }
		             }),
		         32);

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

	REQUIRE(count == 0);
}
