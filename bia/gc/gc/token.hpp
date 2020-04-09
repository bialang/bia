#ifndef BIA_GC_TOKEN_HPP_
#define BIA_GC_TOKEN_HPP_

#include "gc.hpp"
#include "gcable.hpp"
#include "object/header.hpp"
#include "object/pointer.hpp"
#include "stack.hpp"

namespace bia {
namespace gc {

class gc;

/**
 * A token generated by registering the current thread in the gc index. This token manages the gc root.
 */
class token
{
public:
	/**
	 * Move-Constructor.
	 * 
	 * @param[in,out] move the object that should be moved
	*/
	token(token&& move) noexcept : _stack(std::move(move._stack))
	{
		std::swap(_gc, move._gc);
	}
	/**
	 * Destructor.
	 */
	~token() noexcept
	{
		_deregister();
	}
	/**
	 * Sets `dest` to `src`.
	 *
	 * @param[in,out] dest defines the destination
	 * @param src defines the source
	 */
	template<typename T>
	void set(object::pointer<T>& dest, object::pointer<T>& src) noexcept
	{
		set(dest, src.get());
	}
	/**
	 * Sets the destination pointer to the source pointer. If the gc is active, additional work is done.
	 *
	 * @param[out] dest defines the destination
	 * @param src defines the source
	 * @tparam T the type of the pointer
	 */
	template<typename T>
	void set(object::pointer<T>& dest, T* src) noexcept
	{
		// gc is active and dest could be possibly missed
		if (const auto ptr = dest.get()) {
			const auto header = reinterpret_cast<object::header*>(ptr) - 1;

			while (true) {
				auto current_index = _gc->_miss_index.load(std::memory_order_consume);

				if (header->miss_index.exchange(current_index, std::memory_order_release) <= current_index) {
					break;
				}
			}
		}

		dest.set(src);
	}
	/**
	 * Sets the @ref object::pointer at `index` in the root to `src`.
	 *
	 * @param index the index of the @ref object::pointer
	 * @param[in] src the source value
	 * @throw exception::bounds_error if the index is out of bounds
	 */
	void set(std::size_t index, object::base* src)
	{
		set(_stack.at(index), src);
	}
	template<typename T>
	void set(std::size_t index, gcable<T>&& src)
	{
		set(_stack.at(index), src.peek());
		src.start_monitor();
	}
	/**
	 * Returns the internal root object.
	 *
	 * @returns a reference to the root
	 */
	class stack& stack() noexcept
	{
		return _stack;
	}
	token& operator=(token&& move) noexcept
	{
		_deregister();

		_gc      = move._gc;
		_stack   = std::move(move._stack);
		move._gc = nullptr;

		return *this;
	}

private:
	friend gc;

	/** the parent gc */
	gc* _gc = nullptr;
	class stack _stack;

	/**
	 * Constructor.
	 *
	 * @param[in] gc the parent garbage collector
	 * @param count the stack size in elements
	 * @throw see gc::_create_stack()
	 */
	token(gc* gc, std::size_t count) : _stack(gc->_create_stack(count))
	{
		_gc = gc;
	}
	void _deregister() noexcept
	{
		if (_gc) {
			gc::_active_gc_instance = nullptr;

			_gc->_destroy_stack(_stack);
		}
	}
};

} // namespace gc
} // namespace bia

#endif