#ifndef BIA_COMPILER_TYPE_INTEGER_HPP_
#define BIA_COMPILER_TYPE_INTEGER_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
namespace type {

class integer : public definition
{
public:
	enum class size
	{
		i,
		i8,
		i16,
		i32,
		i64,
		u,
		u8,
		u16,
		u32,
		u64
	};

	integer(size size) noexcept : _size{ size }
	{}
	bool is_assignable(const definition* other) const noexcept
	{
		return dynamic_cast<const integer*>(other) && static_cast<const integer*>(other)->_size == _size;
	}
	int hash_code() const noexcept override
	{
		return static_cast<int>(_size) + 1;
	}

private:
	const size _size;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
