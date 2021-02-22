#ifndef BIA_INTERNAL_TYPE_INTEGER_HPP_
#define BIA_INTERNAL_TYPE_INTEGER_HPP_

#include "definition.hpp"

#include <bia/util/aggregate.hpp>

namespace bia {
namespace internal {
namespace type {

class Integer : public Definition
{
public:
	enum class Size
	{
		i8 = 2,
		u8,
		i16 = 4,
		u16,
		i32 = 8,
		u32,
		i64 = 16,
		u64
	};

	Integer(Size size, bool default_size) noexcept : _size{ size }, _default_size{ default_size }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return this == other;
	}
	unsigned int size() const noexcept override
	{
		return static_cast<unsigned int>(_size) / 2;
	}
	int flags() const noexcept override
	{
		return flag_truthable;
	}
	int compare(util::Not_null<const Definition*> other) const noexcept override
	{
		const int n = util::compare(ordinal(), other->ordinal());
		return n == 0 ? util::compare(_size, static_cast<const Integer*>(other.get())->_size,
		                              static_cast<int>(_default_size),
		                              static_cast<int>(static_cast<const Integer*>(other.get())->_default_size))
		              : n;
	}
	unsigned int ordinal() const noexcept override
	{
		return 2;
	}

private:
	const Size _size;
	const bool _default_size;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
