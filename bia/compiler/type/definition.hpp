#ifndef BIA_COMPILER_TYPE_DEFINITION_HPP_
#define BIA_COMPILER_TYPE_DEFINITION_HPP_

namespace bia {
namespace compiler {
namespace type {

class Definition
{
public:
	enum Flag
	{
		flag_truthable = 0x01
	};

	virtual ~Definition()                                              = default;
	virtual bool is_assignable(const Definition* other) const noexcept = 0;
	virtual unsigned int type_code() const noexcept                    = 0;
	virtual unsigned int size() const noexcept                         = 0;
	virtual int flags() const noexcept                                 = 0;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
