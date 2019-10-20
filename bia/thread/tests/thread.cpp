#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <thread/thread.hpp>
#include <exception/interrupt_exception.hpp>

using namespace bia::thread;

TEST_CASE("testing thread", "[thread]")
{
	int t0 = 0;
	thread t([&] { t0 = 30; });

	REQUIRE(t0 == 0);

	t.start();
	t.join();

	REQUIRE(t0 == 30);
}

TEST_CASE("interupting", "[thread]")
{
	auto mt = thread::current_thread();

	thread t([&] { mt.interrupt(); });

	t.start();

	REQUIRE_THROWS_AS(thread::sleep(0), bia::exception::interrupt_exception);

	t.join();
}