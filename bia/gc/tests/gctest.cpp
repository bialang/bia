#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <cstdint>
#include <cstdlib>
#include <gc/gc.hpp>
#include <gc/object.hpp>

using namespace bia::gc;

std::size_t total_allocated_size = 0;

void my_free(void* ptr, std::size_t size)
{
	total_allocated_size -= size;

	free(ptr);
}

void* my_allocate(std::size_t size)
{
	auto ptr = malloc(size);

	if (ptr) {
		total_allocated_size += size;
	}

	return ptr;
}

TEST_CASE("unmonitored memory allocation", "[gc]")
{
	REQUIRE(total_allocated_size == 0);

	SECTION("alignment")
	{
		gc g(sizeof(void*), &my_allocate, &my_free);
		auto ptr1 = g.unmonitored_allocate(6);
		auto ptr2 = g.unmonitored_allocate(6);

		REQUIRE(ptr1 != nullptr);
		REQUIRE(ptr2 != nullptr);
		REQUIRE(ptr1 != ptr2);
		REQUIRE(reinterpret_cast<std::intptr_t>(ptr1) % sizeof(void*) == 0);
		REQUIRE(reinterpret_cast<std::intptr_t>(ptr2) % sizeof(void*) == 0);

		g.unmonitored_free(ptr1, 6);
		g.unmonitored_free(ptr2, 6);
	}

	SECTION("allocating zeroed memory")
	{
		gc g(sizeof(void*), &my_allocate, &my_free);
		auto ptr = static_cast<int8_t*>(g.unmonitored_allocate(16, true));

		REQUIRE(ptr != nullptr);

		for (auto i = 0; i < 16; ++i) {
			if (ptr[i]) {
				FAIL("memory is not zero")
			}
		}

		g.unmonitored_free(ptr);
	}

	REQUIRE(total_allocated_size == 0);
}

TEST_CASE("monitored memory allocation", "[gc]")
{
	REQUIRE(total_allocated_size == 0);

	SECTION("alignment")
	{
		gc g(sizeof(void*), &my_allocate, &my_free);
		auto root = g.create_root<void>(2);

		root[0] = g.allocate(6);
		root[1] = g.allocate(6);

		REQUIRE(root[0] != nullptr);
		REQUIRE(root[1] != nullptr);
		REQUIRE(root[0] != root[1]);
		REQUIRE(reinterpret_cast<std::intptr_t>(root[0]) % sizeof(void*) == 0);
		REQUIRE(reinterpret_cast<std::intptr_t>(root[1]) % sizeof(void*) == 0);
	}

	SECTION("atomatic destruction of monitored objects")
	{
		class test_class : public object
		{
		public:
			test_class(int& destroy_count, gc& g, bool contains_nodes)
				: destroy_count(destroy_count)
			{
				raw_data = g.allocate(7);

				if (contains_nodes) {
					node = g.construct<test_class>(destroy_count, g, false);
				}

				++destroy_count;
			}
			~test_class()
			{
				--destroy_count;
			}

		protected:
			virtual gc_mark_children(bool mark) const override
			{
				gc_mark(raw_data, mark);
				gc_mark(node, mark);
			}

		private:
			int& destroy_count;
			object_ptr<void> raw_data;
			object_ptr<test_class> node;
		};

		gc g(sizeof(void*), &my_allocate, &my_free);
		auto root   = g.create_root<void>(1);
		int counter = 0;

		root[0] = g.construct<test_class>(counter, g, true);

		REQUIRE(counter == 2);

		// Remove reference and force garbage collection
		root[0] = nullptr;
		g.force_synchronous_run(nullptr);

		REQUIRE(counter == 0);
	}

	REQUIRE(total_allocated_size == 0);
}