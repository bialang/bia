#ifndef BIA_INTERNAL_TYPE_OBJECT_HPP_
#define BIA_INTERNAL_TYPE_OBJECT_HPP_

#include "../string_key.hpp"
#include "definition.hpp"
#include "function.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/optional.hpp>
#include <map>

namespace bia {
namespace internal {
namespace type {

class Object : public Definition_base
{
public:
	void add_member(const String_key& name, const Definition_base* type)
	{
		// already defined
		// if (_members.find(name) != _members.end()) {
		// 	BIA_THROW(error::Code::symbol_already_declared);
		// }
		// if (dynamic_cast<const Function*>(type)) {
		// 	_members.insert({ name, { type, _methods++ } });
		// } else {
		// 	_members.insert({ name, { type, _variables++ } });
		// }
	}
	util::Optional<std::pair<const Definition_base*, std::size_t>> get_member(const String_key& name) const
	{
		const auto it = _members.find(name);
		if (it != _members.end()) {
			return it->second;
		}
		return util::nullopt;
	}

private:
	std::size_t _variables = 8;
	std::size_t _methods   = 0;
	std::map<String_key, std::pair<const Definition_base*, std::size_t>, String_comparator> _members;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
