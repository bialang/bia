#ifndef BIA_GC_GCABLE_HPP_
#define BIA_GC_GCABLE_HPP_

#include "gc.hpp"

#include <bia/util/gsl.hpp>
#include <type_traits>

namespace bia {
namespace gc {

/**
 * Contains a gc monitored pointer. This pointer can already be active.
 *
 * @tparam Type the type of the pointer
 */
template<typename Type>
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
	gcable(gc* gc, Type* ptr) noexcept
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
	/**
	 * Move-Constructor.
	 *
	 * @post `move` will be invalid
	 *
	 * @param[in, out] move the move object
	 * @tparam T must be a parent of `Type`
	 */
	template<typename T, typename = typename std::enable_if<std::is_base_of<Type, T>::value>::type>
	gcable(gcable<T>&& move) noexcept
	{
		std::swap(_gc, move._gc);

		_ptr      = static_cast<Type*>(move._ptr);
		move._ptr = nullptr;
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

		_gc->register_gcable(_ptr);

		_gc = nullptr;
	}
	/**
	 * Returns the pointer and releases it without starting to monitor.
	 *
	 * @pre this object is valid
	 * @post this object is invalid
	 */
	Type* release()
	{
		BIA_EXPECTS(valid());

		_gc = nullptr;

		return _ptr;
	}
	/**
	 * Returns the pointer.
	 *
	 * @returns the pointer if this object
	 */
	Type* peek() const noexcept
	{
		return _ptr;
	}
	/**
	 * Checks if this object is valid. An object is only valid if the pointer is not `nullptr` and monitoring
	 * has not started yet.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept
	{
		return _gc && _ptr;
	}
	/*template<typename U>
	typename std::enable_if<std::is_base_of<U, T>::value, gcable<U>>::type to()
	{
		gcable<U> r{ _gc, _ptr };

		_gc  = nullptr;
		_ptr = nullptr;

		return r;
	}*/
	gcable& operator=(gcable&& move) noexcept
	{
		_discard();

		std::swap(_gc, move._gc);
		std::swap(_ptr, move._ptr);

		return *this;
	}
	template<typename T>
	gcable& operator=(gcable<T>&& move) noexcept
	{
		_discard();

		std::swap(_gc, move._gc);

		_ptr      = static_cast<Type*>(move._ptr);
		move._ptr = nullptr;

		return *this;
	}

private:
	template<typename T>
	friend class gcable;

	/** the parent gc */
	gc* _gc = nullptr;
	/** the actual gcable pointer */
	Type* _ptr = nullptr;

	/**
	 * Discards this gcable monitor. If already discarded, this is a noop.
	 *
	 * @post not valid()
	 */
	void _discard() noexcept
	{
		if (_gc) {
			_destroy(util::not_null<Type*>{ _ptr });
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
