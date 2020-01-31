#pragma once

#include <atomic>
#include <memory>

namespace bia {
namespace gc {

/*
 An atmoic pointer to the gc monitored object. This holder object is only required when this is meant to be set several
 times.
*/
class object_ptr
{
public:
	template<typename T = void>
	T* get() noexcept
	{
		return static_cast<T*>(_ptr.load(std::memory_order_consume));
	}
	template<typename T = void>
	const T* get() const noexcept
	{
		return static_cast<const T*>(_ptr.load(std::memory_order_consume));
	}
	template<typename T = void>
	operator T*() noexcept
	{
		return get<T>();
	}
	template<typename T = void>
	operator const T*() const noexcept
	{
		return get<T>();
	}

private:
	friend class gc;

	std::atomic<void*> _ptr;

	/*
	 Constructor.
	 
	 @param ptr is the initial value
	*/
	object_ptr(void* ptr = nullptr) noexcept : _ptr(ptr)
	{}
	void set(void* ptr) noexcept
	{
		_ptr.store(ptr, std::memory_order_release);
	}
};

} // namespace gc
} // namespace bia