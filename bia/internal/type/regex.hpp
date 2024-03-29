#ifndef BIA_INTERNAL_TYPE_REGEX_HPP_
#define BIA_INTERNAL_TYPE_REGEX_HPP_

#include "definition.hpp"

#include <bia/memory/gc/types.hpp>

namespace bia {
namespace internal {
namespace type {

class Regex : public Definition_base
{
public:
	bool is_assignable(const Definition_base* other) const noexcept override
	{
		return dynamic_cast<const Regex*>(other);
	}
	std::size_t size() const noexcept override
	{
		return sizeof(memory::gc::GC_able<memory::gc::Regex*>);
	}
	std::size_t alignment() const noexcept override
	{
		return alignof(memory::gc::GC_able<memory::gc::Regex*>);
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
		return 5;
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
