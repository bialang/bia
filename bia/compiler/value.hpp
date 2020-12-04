#ifndef BIA_COMPILER_VALUE_HPP_
#define BIA_COMPILER_VALUE_HPP_

#include "type/definition.hpp"

#include <cstdint>

namespace bia {
namespace compiler {

class value
{
public:
private:
	type::definition* _type;
	union
	{
		std::int64_t i;
		std::uint64_t u;
		double f;
	} _constant;
	bool _is_constant;
};

} // namespace compiler
} // namespace bia

#endif
