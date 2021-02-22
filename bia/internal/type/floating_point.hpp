#ifndef BIA_INTERNAL_TYPE_FLOATING_POINT_HPP_
#define BIA_INTERNAL_TYPE_FLOATING_POINT_HPP_

#include "definition.hpp"

namespace bia {
namespace internal {
namespace type {

class Floating_point : public Definition
{
public:
	enum class Size
	{
		f32,
		f64
	};

	Floating_point(Size size) noexcept : _size{ size }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Floating_point*>(other) &&
		       static_cast<const Floating_point*>(other)->_size == _size;
	}
	unsigned int size() const noexcept override
	{
		return _size == Size::f32 ? 4 : 8;
	}
	int flags() const noexcept override
	{
		return 0;
	}
	int compare(util::Not_null<const Definition*> other) const noexcept override
	{
		const int n = util::compare(ordinal(), other->ordinal());
		return n == 0 ? util::compare(_size, static_cast<const Floating_point*>(other.get())->_size) : n;
	}
	unsigned int ordinal() const noexcept override
	{
		return 3;
	}

private:
	const Size _size;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
