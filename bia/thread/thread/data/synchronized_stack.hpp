#pragma once

#include <mutex>
#include <utility>

namespace bia {
namespace thread {
namespace data {

template<typename Container, typename Mutex>
class synchronized_stack
{
public:
	typedef typename Container::size_type size_type;
	typedef typename Container::value_type value_type;

	synchronized_stack()
	{}
	synchronized_stack(const Container& container) : container(container)
	{}
	synchronized_stack(Container&& container) : container(std::move(container))
	{}
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

		container.emplace_back(std::forward<Args>(args)...);
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
} // namespace thread
} // namespace bia