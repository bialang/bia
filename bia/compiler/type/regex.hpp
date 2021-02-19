#ifndef BIA_COMPILER_TYPE_REGEX_HPP_
#define BIA_COMPILER_TYPE_REGEX_HPP_

#include "definition.hpp"

#include <bia/memory/gc/types.hpp>

namespace bia {
namespace compiler {
namespace type {

class Regex : public Definition
{
public:
	Regex(unsigned int type_code) noexcept : _type_code{ type_code }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Regex*>(other);
	}
	unsigned int type_code() const noexcept override
	{
		return _type_code;
	}
	unsigned int size() const noexcept override
	{
		return sizeof(memory::gc::Regex*);
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
