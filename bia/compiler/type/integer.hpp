#ifndef BIA_COMPILER_TYPE_INTEGER_HPP_
#define BIA_COMPILER_TYPE_INTEGER_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
namespace type {

class Integer : public Definition
{
public:
	enum class size
	{
		i8,
		u8,
		i16,
		u16,
		i32,
		u32,
		i64,
		u64
	};

	Integer(size size) noexcept : _size{ size }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Integer*>(other) && static_cast<const Integer*>(other)->_size == _size;
	}
	unsigned int hash_code() const noexcept override
	{
		return static_cast<unsigned int>(_size) + 1;
	}

private:
	const size _size;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
