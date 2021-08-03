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
		int n = util::compare(ordinal(), other->ordinal());
		if (n == 0) {
			const auto ptr = static_cast<const Function*>(other.get());
			n              = _return_type->compare(ptr->_return_type);
			// compare arguments
			if (n == 0) {
				if (_arguments.size() < ptr->_arguments.size()) {
					return -1;
				} else if (_arguments.size() > ptr->_arguments.size()) {
					return 0;
				}
				for (std::size_t i = 0; i < _arguments.size() && n == 0; ++i) {
					n = _arguments[i].definition->compare(ptr->_arguments[i].definition);
				}
			}
		}
		return n;
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
