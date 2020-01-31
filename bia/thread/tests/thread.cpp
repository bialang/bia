#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <thread/config.hpp>
#include <thread/thread.hpp>

using namespace bia::thread;

#if !defined(BIA_THREAD_BACKEND_NONE)

TEST_CASE("testing thread", "[thread]")
{
	int t0 = 0;

	REQUIRE(t0 == 0);

	thread t([&] { t0 = 30; });

	t.join();

	REQUIRE(t0 == 30);
}

#endif

/*TEST_CASE("interupting", "[thread]")
{
    auto mt = thread::current_thread();

    thread t([&] { mt.interrupt(); });

    t.start();

    REQUIRE_THROWS_AS(thread::sleep(0), bia::exception::interrupt_exception);

    t.join();
}*/