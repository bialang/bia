#ifndef BIA_COMPILER_TYPE_INTEGER_HPP_
#define BIA_COMPILER_TYPE_INTEGER_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
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

	Integer(unsigned int type_code, Size size) noexcept : _type_code{ type_code }, _size{ size }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return this == other;
	}
	unsigned int type_code() const noexcept override
	{
		return _type_code;
	}
	unsigned int size() const noexcept override
	{
		return static_cast<unsigned int>(_size) / 2;
	}
	int flags() const noexcept override
	{
		return flag_truthable;
	}

private:
	const unsigned int _type_code;
	const Size _size;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
