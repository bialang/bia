#ifndef BIA_INTERNAL_TYPE_FUNCTION_HPP_
#define BIA_INTERNAL_TYPE_FUNCTION_HPP_

#include "definition.hpp"

#include <bia/util/aggregate.hpp>

namespace bia {
namespace internal {
namespace type {

class Function : public Definition
{
public:
	Function(const Definition* return_type) noexcept : _return_type{ return_type }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Function*>(other);
	}
	unsigned int size() const noexcept override
	{
		return sizeof(void*);
	}
	int flags() const noexcept override
	{
		return 0;
	}
	int compare(util::Not_null<const Definition*> other) const noexcept override
	{
		const int n = util::compare(ordinal(), other->ordinal());
		return n == 0 ? _return_type->compare(static_cast<const Function*>(other.get())->_return_type) : n;
	}
	unsigned int ordinal() const noexcept override
	{
		return 6;
	}

private:
	const Definition* _return_type;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
