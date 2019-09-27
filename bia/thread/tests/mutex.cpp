#include <catch.hpp>

#include <thread/thread.hpp>
#include <thread/shared_spin_mutex.hpp>
#include <thread/spin_mutex.hpp>

using namespace bia::thread;

TEST_CASE("spin mutex", "[mutex][thread]")
{
	spin_mutex mutex;
	auto counter = 0;

	mutex.lock();

	thread t([&] {
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

TEST_CASE("shared sping mutex", "[mutex][thread]")
{
    shared_spin_mutex mutex;
    auto counter = 0;
    auto tmp0 = 0;
    auto tmp1 = 0;
    
    mutex.lock();

	thread t0([&] {
		mutex.lock_shared();
		tmp0 = counter;
		mutex.unlock_shared();
	});

	thread t1([&] {
		mutex.lock_shared();
		tmp1 = counter;
		mutex.unlock_shared();
	});

	counter++;
	REQUIRE(counter == 1);
	mutex.unlock();

	mutex.lock();
	counter++;
	mutex.unlock();

	t0.join();
    t1.join();

	REQUIRE(counter == 2);
    REQUIRE((tmp0 == 1 || tmp0 == 2));
    REQUIRE((tmp1 == 1 || tmp1 == 2));
}
