#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <thread>
#include <util/finally.hpp>
#include <util/thread/spin_mutex.hpp>

using namespace bia::util;

TEST_CASE("scope guard 'finally'", "[util]")
{
	auto x = true;

	SECTION("without cancel")
	{
		{
			finally f([&] { x = false; });
		}

		REQUIRE_FALSE(x);
	}

	SECTION("with cancel")
	{
		{
			finally f([&] { x = false; });

			f.cancel();
		}

		REQUIRE(x);
	}
}

TEST_CASE("spin mutex", "[mutex][thread]")
{
	thread::spin_mutex mutex;
	auto counter = 0;

	mutex.lock();

	std::thread t([&] {
		mutex.lock();
		counter++;
		mutex.unlock();
	});

	counter++;
	REQUIRE(counter == 1);
	mutex.unlock();

	mutex.lock();
	counter++;
	mutex.unlock();

	t.join();

	REQUIRE(counter == 3);
}