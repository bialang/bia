#ifndef BIA_COMPILER_TYPE_STRING_HPP_
#define BIA_COMPILER_TYPE_STRING_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
namespace type {

class String : public Definition
{
public:
	String(unsigned int type_code) noexcept : _type_code{ type_code }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const String*>(other);
	}
	unsigned int type_code() const noexcept override
	{
		return _type_code;
	}
	unsigned int size() const noexcept override
	{
		return sizeof(void*) * 2;
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
