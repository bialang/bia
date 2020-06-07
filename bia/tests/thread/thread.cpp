#define CATCH_CONFIG_MAIN

#include <bia/thread/config.hpp>
#include <bia/thread/thread.hpp>
#include <catch.hpp>

using namespace bia::thread;

#if BIA_THREAD_SUPPORTED

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
