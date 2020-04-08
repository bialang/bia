#ifndef BIA_GC_OBJECT_POINTER_HPP_
#define BIA_GC_OBJECT_POINTER_HPP_

#include <atomic>

namespace bia {
namespace gc {

class gc;

namespace object {

template<typename T>
class pointer
{
public:
	T* get() noexcept
	{
		return _ptr.load(std::memory_order_consume);
	}
	const T* get() const noexcept
	{
		return _ptr.load(std::memory_order_consume);
	}

private:
	friend class gc;

	std::atomic<T*> _ptr;

	pointer(T* ptr) noexcept : _ptr{ ptr }
	{}
	void set(T* ptr) noexcept
	{
		_ptr.store(ptr, std::memory_order_release);
	}
};

template<typename T>
class pointer<const T>
{
public:
	pointer(const T* ptr) noexcept
	{
		_ptr = ptr;
	}
	const T* get() noexcept
	{
		return _ptr;
	}

private:
	const T* _ptr;
};

} // namespace object
} // namespace gc
} // namespace bia

#endif