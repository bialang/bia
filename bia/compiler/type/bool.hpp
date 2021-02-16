#ifndef BIA_COMPILER_TYPE_BOOL_HPP_
#define BIA_COMPILER_TYPE_BOOL_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
namespace type {

class Bool : public Definition
{
public:
	Bool(unsigned int type_code) noexcept : _type_code{ type_code }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Bool*>(other);
	}
	unsigned int type_code() const noexcept override
	{
		return _type_code;
	}
	unsigned int size() const noexcept override
	{
		return 1;
	}
	int flags() const noexcept override
	{
		return flag_truthable;
	}

private:
	const unsigned int _type_code;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
