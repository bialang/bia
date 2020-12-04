#ifndef BIA_COMPILER_TYPE_DEFINITION_HPP_
#define BIA_COMPILER_TYPE_DEFINITION_HPP_

#include <cstdint>

namespace bia {
namespace compiler {
namespace type {

class definition
{
public:
	virtual ~definition()                                              = default;
	virtual bool is_assignable(const definition* other) const noexcept = 0;
	virtual int hash_code() const noexcept                             = 0;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
