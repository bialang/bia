#ifndef BIA_INTERNAL_TYPE_OBJECT_HPP_
#define BIA_INTERNAL_TYPE_OBJECT_HPP_

#include "definition.hpp"
#include "function.hpp"

#include <bia/error/exception.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/algorithm.hpp>
#include <bia/util/optional.hpp>
#include <map>
#include <utility>

namespace bia {
namespace internal {
namespace type {

class Object : public Definition
{
public:
	void add_member(const resource::View& name, const Definition* type)
	{
		// already defined
		if (_members.find(name) != _members.end()) {
			BIA_THROW(error::Code::symbol_already_declared);
		}
		if (dynamic_cast<const Function*>(type)) {
			_members.insert({ name, { type, _methods++ } });
		} else {
			_members.insert({ name, { type, _variables++ } });
		}
	}
	util::Optional<std::pair<const Definition*, std::size_t>> get_member(const resource::View& name) const
	{
		const auto it = _members.find(name);
		if (it != _members.end()) {
			return it->second;
		}
		return util::nullopt;
	}
	bool is_assignable(const Definition* other) const noexcept override
	{
		return dynamic_cast<const Object*>(other);
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
		return 12;
	}

private:
	std::size_t _variables;
	std::size_t _methods;
	std::map<resource::View, std::pair<const Definition*, std::size_t>> _members;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
