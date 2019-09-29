#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <thread/thread.hpp>

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