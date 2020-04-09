#ifndef BIA_GC_GCABLE_HPP_
#define BIA_GC_GCABLE_HPP_

#include "gc.hpp"

#include <type_traits>
#include <util/gsl.hpp>

namespace bia {
namespace gc {

template<typename T>
class gcable
{
public:
	gcable() = default;
	/**
	 * Constructor.
	 *
	 * @param[in] gc the gc parent
	 * @param[in] ptr the gcable pointer
	 */
	gcable(gc* gc, T* ptr) noexcept
	{
		_gc  = gc;
		_ptr = ptr;
	}
	/**
	 * Move-Constructor.
	 *
	 * @post `move` will be invalid
	 *
	 * @param[in, out] move the move object
	 */
	gcable(gcable&& move) noexcept
	{
		std::swap(_gc, move._gc);
		std::swap(_ptr, move._ptr);
	}
	~gcable()
	{
		// discard if not monitored
		_discard();
	}
	/**
	 * Starts monitoring this buffer.
	 *
	 * @warning if the pointer has not been successfully saved to root or one of its children the pointer
	 * could be garbage collected
	 *
	 * @pre this object is valid
	 * @post this object invalid
	 */
	void start_monitor()
	{
		BIA_EXPECTS(valid());

		_gc->_register_gcable(_ptr);

		_gc  = nullptr;
		_ptr = nullptr;

		BIA_ENSURES(!valid());
	}
	/**
	 * Returns the gc pointer.
	 *
	 * @returns the pointer if this object is valid, otherwise `nullptr`
	 */
	T* peek() const noexcept
	{
		return _ptr;
	}
	/**
	 * Checks if this object is valid. If so the pointer can be retrieved and/or monitored.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept
	{
		return _gc;
	}
	template<typename U>
	typename std::enable_if<std::is_base_of<U, T>::value, gcable<U>>::type to()
	{
		gcable<U> r{ _gc, _ptr };

		_gc  = nullptr;
		_ptr = nullptr;

		return r;
	}
	gcable& operator=(gcable&& move) noexcept
	{
		_discard();

		std::swap(_gc, move._gc);

		_ptr = move._ptr;

		return *this;
	}

private:
	/** the parent gc */
	gc* _gc = nullptr;
	/** the actual gcable pointer */
	T* _ptr = nullptr;

	/**
	 * Discards this gcable monitor. If already discarded, this is a noop.
	 *
	 * @post not valid()
	 */
	void _discard() noexcept
	{
		if (_gc) {
			_destroy(util::not_null<T*>{ _ptr });
			_gc->_free(_ptr);

			_gc  = nullptr;
			_ptr = nullptr;
		}
	}
	/**
	 * Does nothing.
	 */
	template<typename U>
	static
	    typename std::enable_if<!std::is_destructible<U>::value>::type _destroy(util::not_null<U*>) noexcept
	{}
	/**
	 * Destroys the given object.
	 *
	 * @param ptr the pointer to the object
	 * @tparam U the type of the object
	 */
	template<typename U>
	static typename std::enable_if<std::is_destructible<U>::value>::type
	    _destroy(util::not_null<U*> ptr) noexcept
	{
		ptr->~U();
	}
};

} // namespace gc
} // namespace bia

#endif