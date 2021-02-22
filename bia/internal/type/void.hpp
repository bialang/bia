#ifndef BIA_INTERNAL_TYPE_VOID_HPP_
#define BIA_INTERNAL_TYPE_VOID_HPP_

#include "definition.hpp"

#include <bia/util/aggregate.hpp>

namespace bia {
namespace internal {
namespace type {

class Void : public Definition
{
public:
	bool is_assignable(const Definition* other) const noexcept override
	{
		return true;
	}
	unsigned int size() const noexcept override
	{
		return 0;
	}
	int flags() const noexcept override
	{
		return 0;
	}
	int compare(util::Not_null<const Definition*> other) const noexcept override
	{
		return util::compare(ordinal(), other->ordinal());
	}
	unsigned int ordinal() const noexcept override
	{
		return 0;
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
