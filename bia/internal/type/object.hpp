#ifndef BIA_INTERNAL_TYPE_OBJECT_HPP_
#define BIA_INTERNAL_TYPE_OBJECT_HPP_

#include "../string_key.hpp"
#include "definition.hpp"
#include "framer.hpp"

#include <bia/error/exception.hpp>
#include <bia/member/object/base.hpp>
#include <bia/util/optional.hpp>
#include <bia/util/variant.hpp>
#include <map>

namespace bia {
namespace internal {
namespace type {

struct Variable
{
	enum Flag
	{
		flag_mutable = 0x1
	};

	std::size_t offset;
	const type::Definition_base* definition;
	int flags;
};

struct Dynamic_object
{};

template<>
class Definition<Dynamic_object> : public Definition_base
{
public:
	typedef util::Variant<Variable, const type::Definition_base*> Symbol;
	typedef std::map<String_key, Symbol, String_comparator> Map;

	Definition(Map members) noexcept : _members{ std::move(members) }
	{}
	bool is_assignable(const Definition_base* other) const noexcept override
	{
		return compare(other) == 0;
	}
	std::size_t size() const noexcept override
	{
		return sizeof(memory::gc::GC_able<member::object::Base*>);
	}
	std::size_t alignment() const noexcept override
	{
		return alignof(memory::gc::GC_able<member::object::Base*>);
	}
	int flags() const noexcept override
	{
		return 0;
	}
	int compare(util::Not_null<const Definition_base*> other) const noexcept override
	{
		int n = util::compare(ordinal(), other->ordinal());
		if (n == 0) {
			const auto ptr = static_cast<const Definition*>(other.get());
			n              = util::compare(_members.size(), ptr->_members.size());
			for (auto it = _members.begin(), jt = ptr->_members.begin(); n == 0 && it != _members.end();
			     ++it, ++jt) {
				if ((n = internal::compare(it->first, jt->first)) == 0) {
					if ((n = util::compare(it->second.index(), jt->second.index())) == 0) {
						if (it->second.is_type<Variable>()) {
							n = it->second.get<Variable>().definition->compare(jt->second.get<Variable>().definition);
						} else if (it->second.is_type<const Definition_base*>()) {
							n = it->second.get<const Definition_base*>()->compare(jt->second.get<const Definition_base*>());
						}
					}
				}
			}
		}
		return n;
	}
	unsigned int ordinal() const noexcept override
	{
		return 37;
	}
	Symbol get_member(const String_key& name) const
	{
		const auto it = _members.find(name);
		if (it != _members.end()) {
			return it->second;
		}
		return {};
	}

private:
	Map _members;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
