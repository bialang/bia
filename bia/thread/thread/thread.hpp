#pragma once

#include <cstdint>
#include <functional>
#include <memory>

namespace bia {
namespace thread {

class thread final
{
public:
	thread(std::function<void()> target);
	~thread();
	static void yield();
	/*
	 Blocks the execution of the current thread for `duration` milliseconds. If the thread is interrupted an exception
	 is thrown.

	 @param duration is the length of the sleep in milliseconds
	 @throws exception::interrupt_exception if the thread was interrupted
	*/
	static void sleep(std::uintmax_t duration);
	static thread current_thread();
	void join();
	void start();
	void interrupt();
	void daemon(bool daemon);
	bool daemon() const noexcept;
	bool alive() const noexcept;
	bool interrupted() const noexcept;

private:
	struct impl;

	std::shared_ptr<impl> pimpl;
};

} // namespace thread
} // namespace bia