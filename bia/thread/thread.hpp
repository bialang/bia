#ifndef BIA_THREAD_THREAD_HPP_
#define BIA_THREAD_THREAD_HPP_

#include "config.hpp"

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>

namespace bia {
namespace thread {

/**
 * A threading class with automatic joining.
 */
class Thread
{
public:
	/** the type of the function to run in the thread */
	typedef std::function<void()> target_type;

	/**
	 * Initializes this thread with the function and runs it immediately if valid.
	 *
	 * @param target (optional) the function that should be run
	 * @throw exception::unsupported_error if threading is not supported
	 */
	Thread(target_type target = {});
	~Thread();
	static void yield();
	/**
	 * Blocks the execution of the current thread for the given duration. If the thread is interrupted, an
	 * exception will be thrown.
	 *
	 * @post the interrupt flag will be cleared
	 *
	 * @param duration the duration in milliseconds; `0` causes the thread to block indefinitely
	 * @throw exception::interrupt_error if this thread was interrupted
	 */
	static void sleep(std::chrono::milliseconds duration);
	/// Blocks and waits for this running thread.
	void join();
	void detach();
	/// Checks if this thread is valid. A thread is valid if it was initialized with a target and threading is
	/// supported. See supported() for more information.
	bool valid() const noexcept;
	/// Checks whether threading is supported by the Bialang libarary.
	static bool supported() noexcept;

private:
	struct Impl;

	std::shared_ptr<Impl> _pimpl;
};

} // namespace thread
} // namespace bia

#endif
