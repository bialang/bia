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

class tracking_allocator : public simple_allocator
{
public:
	virtual void deallocate(void* ptr, std::size_t previous_size) override
	{
		allocated.erase(static_cast<std::int8_t*>(ptr) + previous_size);

		simple_allocator::deallocate(ptr, previous_size);
	}
	virtual void* allocate(std::size_t size, std::size_t previous_size) override
	{
		auto ptr = simple_allocator::allocate(size, previous_size);

		allocated.insert(static_cast<std::int8_t*>(ptr) + previous_size);

		return ptr;
	}
	bool has(const void* ptr) const noexcept
	{
		return allocated.find(ptr) != allocated.end();
	}
	std::size_t allocation_count() const noexcept
	{
		return allocated.size();
	}

private:
	std::set<const void*> allocated;
};

std::unique_ptr<gc> create_gc()
{
	return std::unique_ptr<gc>(
		new gc(std::unique_ptr<memory_allocator>(new tracking_allocator()), nullptr));
}

TEST_CASE("unmonitored memory allocation", "[gc]")
{
	auto g	= create_gc();
	auto ptr1 = g->allocator()->allocate(6, 0);
	auto ptr2 = g->allocator()->allocate(6, 0);
	
	REQUIRE(ptr1 != nullptr);
	REQUIRE(ptr2 != nullptr);
	REQUIRE(ptr1 != ptr2);
	REQUIRE(reinterpret_cast<std::intptr_t>(ptr1) % sizeof(void*) == 0);
	REQUIRE(reinterpret_cast<std::intptr_t>(ptr2) % sizeof(void*) == 0);

	g->allocator()->deallocate(ptr1, 0);
	g->allocator()->deallocate(ptr2, 0);

	REQUIRE(static_cast<tracking_allocator*>(g->allocator())->allocation_count() == 0);
}

TEST_CASE("garbage collection test", "[gc]")
{
	auto g = create_gc();
	auto allocator = static_cast<tracking_allocator*>(g->allocator());
	void* p0;
	void* p1;
	void* p2;

	SECTION("collection of leafs")
	{
		auto token = g->register_thread(2u);

		token.set(0, 0, p0 = g->allocate(59));
		token.set(0, 1, p1 = g->allocate(23));
		token.set(0, 0, p2 = g->allocate(12));

		REQUIRE(allocator->has(p0));
		REQUIRE(allocator->has(p1));
		REQUIRE(allocator->has(p2));

		// collect p0
		g->run_synchronously();

		REQUIRE(!allocator->has(p0));
		REQUIRE(allocator->has(p1));
		REQUIRE(allocator->has(p2));
	}

	// run garbage collector
	g->run_synchronously();

	REQUIRE(!allocator->has(p0));
	REQUIRE(!allocator->has(p1));
	REQUIRE(!allocator->has(p2));
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