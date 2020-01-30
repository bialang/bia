#pragma once

#include <cstddef>
#include <functional>

namespace bia {
namespace thread {

class thread_pool
{
public:
	struct context
	{};

	virtual ~thread_pool() = default;

	static unsigned int hardware_concurrency() noexcept;
	virtual void execute(const std::function<void()>& task)         = 0;
	virtual void execute(const std::function<void(context&)>& task) = 0;
	virtual void execute(std::function<void()>&& task)              = 0;
	virtual void execute(std::function<void(context&)>&& task)      = 0;
	virtual std::size_t pool_size() const noexcept                  = 0;
	virtual std::size_t max_pool_size() const noexcept              = 0;
	virtual std::size_t task_count() const noexcept                 = 0;
};

} // namespace thread
} // namespace bia