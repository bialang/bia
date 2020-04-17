#ifndef BIA_GC_OBJECT_POINTER_HPP_
#define BIA_GC_OBJECT_POINTER_HPP_

#include <atomic>

namespace bia {
namespace gc {

class token;

namespace object {

template<typename T>
class pointer
{
public:
	pointer(T* ptr) noexcept : _ptr{ ptr }
	{}
	T* get() noexcept
	{
		return _ptr.load(std::memory_order_consume);
	}
	const T* get() const noexcept
	{
		return _ptr.load(std::memory_order_consume);
	}
	T& operator*() noexcept
	{
		return *get();
	}
	const T& operator*() const noexcept
	{
		return *get();
	}
	T* operator->() noexcept
	{
		return _ptr;
	}
	const T* operator->() const noexcept
	{
		return _ptr;
	}
	operator T*() noexcept
	{
		return get();
	}
	operator const T*() const noexcept
	{
		return get();
	}

private:
	friend token;

	std::atomic<T*> _ptr;

	void set(T* ptr) noexcept
	{
		_ptr.store(ptr, std::memory_order_release);
	}
};

template<typename T>
class immutable_pointer
{
public:
	immutable_pointer(T* ptr) noexcept : _ptr{ ptr }
	{}
	T* get() const noexcept
	{
		return _ptr;
	}
	T& operator*() const noexcept
	{
		return *_ptr;
	}
	T* operator->() const noexcept
	{
		return _ptr;
	}

private:
	T* const _ptr;
};

} // namespace object
} // namespace gc
} // namespace bia

#endif