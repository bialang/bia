#ifndef BIA_INTERNAL_TYPE_BOOL_HPP_
#define BIA_INTERNAL_TYPE_BOOL_HPP_

#include "definition.hpp"

namespace bia {
namespace internal {
namespace type {

template<>
class Definition<bool> : public Definition_helper<bool>
{
public:
	int flags() const noexcept override
	{
		return flag_truthable;
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
