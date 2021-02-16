#ifndef BIA_COMPILER_TYPE_VOID_HPP_
#define BIA_COMPILER_TYPE_VOID_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
namespace type {

class Void : public Definition
{
public:
	Void(unsigned int type_code) noexcept : _type_code{ type_code }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return true;
	}
	unsigned int type_code() const noexcept override
	{
		return _type_code;
	}
	unsigned int size() const noexcept override
	{
		return 0;
	}
	int flags() const noexcept override
	{
		return 0;
	}

private:
	const unsigned int _type_code;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
