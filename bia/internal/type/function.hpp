#ifndef BIA_INTERNAL_TYPE_FUNCTION_HPP_
#define BIA_INTERNAL_TYPE_FUNCTION_HPP_

#include "definition.hpp"

#include <bia/util/algorithm.hpp>
#include <vector>

namespace bia {
namespace internal {
namespace type {

struct Argument
{
	const Definition* definition;
};

class Function : public Definition
{
public:
	Function(const Definition* return_type, std::vector<Argument> arguments) noexcept
	    : _return_type{ return_type }, _arguments{ std::move(arguments) }
	{}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Function*>(other);
	}
	std::size_t size() const noexcept override
	{
		return sizeof(void*);
	}
	std::size_t alignment() const noexcept override
	{
		return 1;
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
	const Definition* return_type() const noexcept
	{
		return _return_type;
	}
	const std::vector<Argument>& arguments() const noexcept
	{
		return _arguments;
	}

private:
	const Definition* _return_type;
	std::vector<Argument> _arguments;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
