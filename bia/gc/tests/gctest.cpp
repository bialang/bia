#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <cstdint>
#include <cstdlib>
#include <gc/gc.hpp>
#include <gc/object.hpp>
#include <gc/simple_allocator.hpp>
#include <memory>
#include <set>

using namespace bia::gc;

std::set<void*> allocated;

void my_free(void* ptr)
{
	allocated.erase(ptr);

	free(ptr);
}

void* my_allocate(std::size_t size)
{
	auto ptr = malloc(size);

	if (ptr) {
		allocated.insert(ptr);
	}

	return ptr;
}

std::unique_ptr<gc> create_gc()
{
	return std::unique_ptr<gc>(
		new gc(std::unique_ptr<memory_allocator>(new simple_allocator(&my_allocate, &my_free)), nullptr));
}

TEST_CASE("unmonitored memory allocation", "[gc]")
{
	REQUIRE(allocated.size() == 0);

	SECTION("alignment")
	{
		auto g	= create_gc();
		auto ptr1 = g->allocator()->allocate(6, 0);
		auto ptr2 = g->allocator()->allocate(6, 0);

		REQUIRE(ptr1 != nullptr);
		REQUIRE(ptr2 != nullptr);
		REQUIRE(ptr1 != ptr2);
		REQUIRE(allocated.size() == 2);
		REQUIRE(reinterpret_cast<std::intptr_t>(ptr1) % sizeof(void*) == 0);
		REQUIRE(reinterpret_cast<std::intptr_t>(ptr2) % sizeof(void*) == 0);

		g->allocator()->deallocate(ptr1, 0);
		g->allocator()->deallocate(ptr2, 0);
	}

	REQUIRE(allocated.size() == 0);
}

TEST_CASE("garbage collection test", "[gc]")
{
	REQUIRE(allocated.size() == 0);

	auto g = create_gc();

	SECTION("collection of leafs")
	{
		auto token = g->register_thread(2u);

		token.set(0, 0, g->allocate(59));
		token.set(0, 1, g->allocate(23));
	}

	SECTION("destruction of objects")
	{

	}

	REQUIRE(allocated.size() == 0);
}
/*
TEST_CASE("monitored memory allocation", "[gc]")
{
	REQUIRE(allocated.size() == 0);

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
			test_class(int& destroy_count, gc& g, bool contains_nodes) : destroy_count(destroy_count)
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
}*/