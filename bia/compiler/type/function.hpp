#ifndef BIA_COMPILER_TYPE_FUNCTION_HPP_
#define BIA_COMPILER_TYPE_FUNCTION_HPP_

#include "definition.hpp"

namespace bia {
namespace compiler {
namespace type {

class Function : public Definition
{
public:
	Function(unsigned int type_code) noexcept : _type_code{ type_code }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Function*>(other);
	}
	unsigned int type_code() const noexcept override
	{
		return _type_code;
	}
	unsigned int size() const noexcept override
	{
		return sizeof(void*);
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
