#ifndef BIA_COMPILER_TYPE_DEFINITION_HPP_
#define BIA_COMPILER_TYPE_DEFINITION_HPP_

namespace bia {
namespace compiler {
namespace type {

class Definition
{
public:
	virtual ~Definition()                                              = default;
	virtual bool is_assignable(const Definition* other) const noexcept = 0;
	virtual unsigned int hash_code() const noexcept                    = 0;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
