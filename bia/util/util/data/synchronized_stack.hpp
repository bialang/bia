#pragma once

#include <mutex>
#include <stack>
#include <utility>

namespace bia {
namespace util {
namespace data {

template<typename Container, typename Mutex>
class synchronized_stack
{
public:
	typedef Container::size_type size_type;
	typedef Container::value_type value_type;

	void push(const value_type& x)
	{
		std::lock_guard<Mutex> lock(mutex);

		container.push_back(x);
	}
	void push(value_type&& x)
	{
		std::lock_guard<Mutex> lock(mutex);

		container.push_back(std::move(x));
	}
	template<typename... Args>
	void emplace(Args&&... args)
	{
		std::lock_guard<Mutex> lock(mutex);

		container.emplace_back(std::move(x));
	}
	bool empty() const noexcept
	{
		std::lock_guard<Mutex> lock(mutex);

		return container.empty();
	}
	size_type size() const noexcept
	{
		std::lock_guard<Mutex> lock(mutex);

		return container.size();
	}
	bool pop(value_type& out) noexcept
	{
		std::lock_guard<Mutex> lock(mutex);

		if (container.empty()) {
			return false;
		}

		out = container.back();

		return true;
	}

private:
	Mutex mutex;
	Container container;
};

} // namespace data
} // namespace util
} // namespace bia