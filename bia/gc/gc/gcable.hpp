#ifndef BIA_GC_GCABLE_HPP_
#define BIA_GC_GCABLE_HPP_

#include "gc.hpp"

#include <util/gsl.hpp>

namespace bia {
namespace gc {

class gc;

template<typename T>
class gcable
{
public:
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
	gcable& operator=(gcable&& move) noexcept
	{
		_discard();

		std::swap(_gc, move._gc);

		_ptr = move._ptr;

		return *this;
	}

private:
	friend gc;

	/** the parent gc */
	gc* _gc = nullptr;
	/** the actual gcable pointer */
	T* _ptr = nullptr;

	/**
	 * Constructor.
	 *
	 * @param[in] gc the gc parent
	 * @param[in] ptr the gcable pointer
	 */
	gcable(util::not_null<gc*> gc, util::not_null<T*> ptr) noexcept
	{
		_gc  = gc.get();
		_ptr = ptr.get();
	}
	/**
	 * Discards this gcable monitor. If already discarded, this is a noop.
	 * 
	 * @post not valid()
	*/
	void _discard() noexcept
	{
		if (_gc) {
			_destroy(_ptr);
			_gc->_free(_ptr);

			_gc  = nullptr;
			_ptr = nullptr;
		}
	}
	/**
	 * Does nothing.
	 */
	static void _destroy(void*) noexcept
	{}
	/**
	 * Destroys the given object.
	 *
	 * @param ptr the pointer to the object
	 * @tparam Ty the type of the object
	 */
	template<typename Ty>
	static void _destroy(util::not_null<Ty*> ptr) noexcept
	{
		ptr->~Ty();
	}
};

} // namespace gc
} // namespace bia

#endif