#ifndef BIA_GC_STACK_VIEW_HPP_
#define BIA_GC_STACK_VIEW_HPP_

#include "object/base.hpp"
#include "object/pointer.hpp"

#include <bia/error/exception.hpp>
#include <utility>
#include <vector>

namespace bia {
namespace member {

class member;

} // namespace member
namespace gc {

class stack_view
{
public:
	struct call_frame;

	typedef object::pointer<member::member> element_type;

	stack_view(element_type* base, std::size_t size) noexcept : _base{ base }, _max_size{ size }
	{
		_last_push = _max_size;
	}
	void prep_call()
	{
		_arg_frames.push_back({ _last_push, 0 });
	}
	/**
	 * Pushes a new element onto the argument stack part.
	 *
	 * @return the newly pushed element
	 * @throw exception::bounds_error if the push could overwrite the local space
	 */
	element_type& push()
	{
		if (_last_push - 1 <= _cursor) {
			BIA_THROW(error::code::out_of_bounds);
		}

		return _base[--_last_push];
	}
	element_type& local_at(std::size_t index)
	{
		if (index >= _max_size) {
			BIA_THROW(error::code::out_of_bounds);
		} else if (index > _cursor) {
			_cursor = index;
		}

		return _base[index];
	}
	element_type& local_at(std::size_t index) const
	{
		if (index > _cursor) {
			BIA_THROW(error::code::out_of_bounds);
		}

		return _base[index];
	}
	element_type& arg_at(std::size_t index) const
	{
		if (index >= _max_size) {
			BIA_THROW(error::code::out_of_bounds);
		}

		return _base[_max_size - index - 1];
	}
	/**
	 * Returns the last pushed argument.
	 *
	 * @return the last pushed argument
	 * @throw exception::bounds_error if no argument was pushed
	 */
	element_type& last_push() const
	{
		if (_last_push == _max_size) {
			BIA_THROW(error::code::out_of_bounds);
		}

		return _base[_last_push];
	}
	void mark_kwarg()
	{
		if (_last_push == _max_size || _arg_frames.empty()) {
			BIA_THROW(error::code::out_of_bounds);
		}

		if (!_arg_frames.back().second) {
			_arg_frames.back().second = _last_push;
		}
	}
	call_frame make_call_frame();

private:
	friend class token;

	element_type* const _base;
	const std::size_t _max_size;
	std::size_t _cursor = 0;
	std::size_t _last_push;
	std::vector<std::pair<std::size_t, std::size_t>> _arg_frames;
};

struct stack_view::call_frame
{
	stack_view stack;
	std::size_t arg_count;
	std::size_t kwarg_count;
};

inline stack_view::call_frame stack_view::make_call_frame()
{
	if (_arg_frames.empty()) {
		BIA_THROW(error::code::out_of_bounds);
	}

	const auto arg_frame = _arg_frames.back();
	call_frame frame{ { _base + _cursor + 1, arg_frame.first - (_cursor + 1) }, 0, 0 };

	frame.kwarg_count = arg_frame.second ? arg_frame.second - _last_push + 1 : 0;
	frame.arg_count   = arg_frame.first - _last_push - frame.kwarg_count;
	_last_push        = arg_frame.first;

	_arg_frames.pop_back();

	return frame;
}

} // namespace gc
} // namespace bia

#endif
