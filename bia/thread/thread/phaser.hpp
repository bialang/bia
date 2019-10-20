#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>

namespace bia {
namespace thread {

class phaser
{
public:
	phaser(std::size_t parties = 0)
	{
		current_phase   = 1;
		arrived_parties = 0;
		this->parties   = parties;
	}
	std::size_t arrive(std::size_t parties = 1)
	{
		std::lock_guard<std::mutex> lock(mutex);

		// Advance to next phase
		if ((arrived_parties += parties) >= this->parties) {
			halter.notify_all();

			return current_phase++;
		}

		return current_phase;
	}
	std::size_t arrive_and_wait()
	{
		std::unique_lock<std::mutex> lock(mutex);

		auto p = current_phase;

		// Advance to next phase
		if (++arrived_parties >= parties) {
			halter.notify_all();

			return current_phase++;
		} else {
			halter.wait(lock, [this, p] { return p < current_phase; });
		}

		return current_phase;
	}
	std::size_t wait(std::size_t phase)
	{
		std::unique_lock<std::mutex> lock(mutex);

		// Advance to next phase
		if (phase >= current_phase) {
			halter.wait(lock, [this, phase] { return current_phase < phase; });
		}

		return current_phase;
	}
	std::size_t register_party(std::size_t count = 1)
	{
		std::lock_guard<std::mutex> lock(mutex);

		parties += count;

		return current_phase;
	}
	std::size_t phase() const
	{
		std::lock_guard<std::mutex> lock(mutex);

		return current_phase;
	}

private:
	std::mutex mutex;
	std::condition_variable halter;
	std::size_t current_phase;
	std::size_t arrived_parties;
	std::size_t parties;
};

} // namespace thread
} // namespace bia