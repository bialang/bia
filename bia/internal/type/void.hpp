#ifndef BIA_INTERNAL_TYPE_VOID_HPP_
#define BIA_INTERNAL_TYPE_VOID_HPP_

#include "definition.hpp"

#include <bia/util/algorithm.hpp>

namespace bia {
namespace internal {
namespace type {

template<>
class Definition<void> : public Definition_base
{
public:
	bool is_assignable(const Definition_base* other) const noexcept override
	{
		return true;
	}
	std::size_t size() const noexcept override
	{
		return 0;
	}
	std::size_t alignment() const noexcept override
	{
		return 1;
	}
	int flags() const noexcept override
	{
		return 0;
	}
	int compare(util::Not_null<const Definition_base*> other) const noexcept override
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
