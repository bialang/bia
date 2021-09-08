#ifndef BIA_INTERNAL_TYPE_OBJECT_HPP_
#define BIA_INTERNAL_TYPE_OBJECT_HPP_

#include "../string_key.hpp"
#include "definition.hpp"
#include "framer.hpp"

#include <bia/error/exception.hpp>
#include <bia/member/object/base.hpp>
#include <bia/util/optional.hpp>
#include <map>

namespace bia {
namespace internal {
namespace type {

struct Member
{
	const Definition_base* definition;
	std::size_t offset;
};

struct Dynamic_object
{};

template<>
class Definition<Dynamic_object> : public Definition_base
{
public:
	typedef std::map<String_key, Member, String_comparator> Map;

	Definition(Map members) noexcept : _members{ std::move(members) }
	{}
	bool is_assignable(const Definition_base* other) const noexcept override
	{
		return compare(other) == 0;
	}
	std::size_t size() const noexcept override
	{
		// TODO
		return 0;
	}
	std::size_t alignment() const noexcept override
	{
		// TODO
		return 0;
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
			for (auto it = _members.begin(); n == 0 && it != _members.end(); ++it) {
				// TODO implement this
				BIA_ASSERT(false);
			}
		}
		return n;
	}
	unsigned int ordinal() const noexcept override
	{
		return 37;
	}
	util::Optional<Member> get_member(const String_key& name) const
	{
		const auto it = _members.find(name);
		if (it != _members.end()) {
			return it->second;
		}
		return util::nullopt;
	}

private:
	Map _members;
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
