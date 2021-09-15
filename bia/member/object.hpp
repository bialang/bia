#ifndef BIA_MEMBER_OBJECT_HPP_
#define BIA_MEMBER_OBJECT_HPP_

#include <bia/memory/frame.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <bia/util/algorithm.hpp>
#include <cstdint>

namespace bia {
namespace member {

class Object : public memory::gc::Base
{
public:
	Object(memory::gc::GC& gc, std::size_t size)
	    : _frame{ { static_cast<util::Byte*>(gc.allocator()->checked_allocate(size).get()), size }, gc }
	{}
	Object(const Object& copy) = delete;
	Object(Object&& move) noexcept : _frame{ move._frame }
	{
		std::swap(_offset, move._offset);
		move._frame = memory::Frame<true>{ { nullptr, +0 }, _frame.gc() };
	}
	~Object() noexcept
	{
		_clear();
	}
	memory::Frame<true> frame() noexcept
	{
		return _frame;
	}
	memory::Frame<false> frame() const noexcept
	{
		return _frame;
	}
	Object& operator=(const Object& copy) = delete;
	Object& operator                      =(Object&& move) noexcept
	{
		_clear();
		_offset      = move._offset;
		move._offset = 0;
		move._frame  = memory::Frame<true>{ { nullptr, +0 }, _frame.gc() };
		return *this;
	}

protected:
	template<typename Type>
	std::int32_t store(const Type& value)
	{
		const std::size_t written = _frame.store(_offset, value);
		const std::int32_t offset = _offset;
		_offset += util::aligned(written, alignof(std::max_align_t));
		return offset;
	}

private:
	memory::Frame<true> _frame;
	std::size_t _offset = 0;

	void _clear() noexcept
	{
		if (_frame.underlying_memory().data()) {
			_frame.gc().allocator()->deallocate(_frame.underlying_memory().data());
		}
	}
};

} // namespace member
} // namespace bia

#endif
