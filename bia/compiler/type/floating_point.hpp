#ifndef BIA_COMPILER_TYPE_FLOATING_POINT_HPP_
#define BIA_COMPILER_TYPE_FLOATING_POINT_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
namespace type {

class Floating_point : public Definition
{
public:
	enum class Size
	{
		f32,
		f64
	};

	Floating_point(unsigned int type_code, Size size) noexcept : _type_code{ type_code }, _size{ size }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Floating_point*>(other) &&
		       static_cast<const Floating_point*>(other)->_size == _size;
	}
	unsigned int type_code() const noexcept override
	{
		return _type_code;
	}
	unsigned int size() const noexcept override
	{
		return _size == Size::f32 ? 4 : 8;
	}
	int flags() const noexcept override
	{
		return 0;
	}

private:
	const Size _size;
	const unsigned int _type_code;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
