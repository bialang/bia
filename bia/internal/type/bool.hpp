#ifndef BIA_INTERNAL_TYPE_BOOL_HPP_
#define BIA_INTERNAL_TYPE_BOOL_HPP_

#include "definition.hpp"

#include <bia/util/algorithm.hpp>

namespace bia {
namespace internal {
namespace type {

class Bool : public Definition
{
public:
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Bool*>(other);
	}
	std::size_t size() const noexcept override
	{
		return 1;
	}
	std::size_t alignment() const noexcept override
	{
		return 1;
	}
	int flags() const noexcept override
	{
		return flag_truthable;
	}
	int compare(util::Not_null<const Definition*> other) const noexcept override
	{
		return util::compare(ordinal(), other->ordinal());
	}
	unsigned int ordinal() const noexcept override
	{
		return 1;
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
