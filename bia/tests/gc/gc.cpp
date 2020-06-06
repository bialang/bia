#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <cstdint>
#include <cstdlib>
#include <gc/gc.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <gc/object/header.hpp>
#include <gc/token.hpp>
#include <memory>
#include <set>

using namespace bia::gc;

class tracking_allocator : public memory::simple_allocator
{
public:
	virtual void deallocate(void* ptr) override
	{
		allocated.erase(static_cast<std::int8_t*>(ptr));

		simple_allocator::deallocate(ptr);
	}
	virtual void* allocate(std::size_t size) override
	{
		auto ptr = simple_allocator::allocate(size);

		allocated.insert(static_cast<std::int8_t*>(ptr));

		return ptr;
	}
	bool has(const void* ptr) const noexcept
	{
		return allocated.find(ptr) != allocated.end();
	}
	bool has_object(const void* ptr) const noexcept
	{
		return allocated.find(static_cast<const object::header*>(ptr) - 1) != allocated.end();
	}
	std::size_t allocation_count() const noexcept
	{
		return allocated.size();
	}

private:
	std::set<const void*> allocated;
};

inline std::unique_ptr<gc> create_gc(std::shared_ptr<memory::allocator> allocator = nullptr)
{
	return std::unique_ptr<gc>(
	    new gc(allocator ? allocator : std::shared_ptr<memory::allocator>(new tracking_allocator())));
}

TEST_CASE("unmonitored memory allocation", "[gc]")
{
	auto g    = create_gc();
	auto ptr1 = g->allocator()->allocate(6);
	auto ptr2 = g->allocator()->allocate(6);

	REQUIRE(ptr1 != nullptr);
	REQUIRE(ptr2 != nullptr);
	REQUIRE(ptr1 != ptr2);
	REQUIRE(reinterpret_cast<std::intptr_t>(ptr1) % sizeof(void*) == 0);
	REQUIRE(reinterpret_cast<std::intptr_t>(ptr2) % sizeof(void*) == 0);

	g->allocator()->deallocate(ptr1);
	g->allocator()->deallocate(ptr2);

	REQUIRE(static_cast<tracking_allocator*>(g->allocator().get())->allocation_count() == 0);
}

TEST_CASE("garbage collection test", "[gc]")
{
	auto allocator = std::make_shared<tracking_allocator>();
	auto g         = create_gc(allocator);

	/*SECTION("collection of leafs")
	{
		auto token = g->register_thread(2);

		auto p0 = set_root_at(token, *g, 0);
		auto p1 = set_root_at(token, *g, 1);

		REQUIRE(allocator->has_object(p0));
		REQUIRE(allocator->has_object(p1));

		auto p2 = set_root_at(token, *g, 0);

		REQUIRE(allocator->has_object(p2));

		// collect p0
		g->run_once();

		REQUIRE(!allocator->has_object(p0));
		REQUIRE(allocator->has_object(p1));
		REQUIRE(allocator->has_object(p2));
	}*/

	SECTION("collection of members")
	{
		
	}

	// free all memory
	g = nullptr;

	REQUIRE(allocator->allocation_count() == 0);
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