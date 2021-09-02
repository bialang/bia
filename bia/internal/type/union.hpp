#ifndef BIA_INTERNAL_TYPE_UNION_HPP_
#define BIA_INTERNAL_TYPE_UNION_HPP_

#include "definition.hpp"

#include <bia/util/algorithm.hpp>
#include <bia/util/variant.hpp>
#include <tuple>
#include <vector>

namespace bia {
namespace internal {
namespace type {

struct Dynamic_union
{};

class Definition_union_base : public Definition_base
{
public:
	bool is_assignable(const Definition_base* other) const noexcept override
	{
		for (auto it = union_begin(); it != union_end(); ++it) {
			if ((*it)->is_assignable(other)) {
				return true;
			}
		}
		return compare(other) == 0;
	}
	std::size_t size() const noexcept override
	{
		std::size_t max = 0;
		for (auto it = union_begin(); it != union_end(); ++it) {
			max = util::max(max, (*it)->size());
		}
		return max;
	}
	std::size_t alignment() const noexcept override
	{
		std::size_t max = 1;
		for (auto it = union_begin(); it != union_end(); ++it) {
			max = util::max(max, (*it)->alignment());
		}
		return max;
	}
	int flags() const noexcept override
	{
		return 0;
	}
	int compare(util::Not_null<const Definition_base*> other) const noexcept override
	{
		int n = util::compare(ordinal(), other->ordinal());
		if (n == 0) {
			const auto ptr = static_cast<const Definition_union_base*>(other.get());
			n              = util::compare(std::distance(union_begin(), union_end()),
                        std::distance(ptr->union_begin(), ptr->union_end()));
			for (auto i = union_begin(), j = ptr->union_begin(); n == 0 && i != union_end(); ++i, ++j) {
				n = util::compare(*i, *j);
			}
		}
		return n;
	}
	unsigned int ordinal() const noexcept override
	{
		return 57;
	}
	virtual const Definition_base* const* union_begin() const noexcept = 0;
	virtual const Definition_base* const* union_end() const noexcept   = 0;
};

template<>
class Definition<Dynamic_union> : public Definition_union_base
{
public:
	Definition(std::vector<const Definition_base*> definitions) noexcept
	    : _definitions{ std::move(definitions) }
	{}
	const Definition_base* const* union_begin() const noexcept override
	{
		return _definitions.empty() ? nullptr : &_definitions.front();
	}
	const Definition_base* const* union_end() const noexcept override
	{
		return _definitions.empty() ? nullptr : &_definitions.back() + 1;
	}

private:
	std::vector<const Definition_base*> _definitions;
};

template<typename... Types>
class Definition<util::Variant<Types...>> : public Definition_union_base
{
public:
	Definition() noexcept
	{
		_fill_pointers<0, Types...>();
	}
	const Definition_base* const* union_begin() const noexcept override
	{
		return _pointers;
	}
	const Definition_base* const* union_end() const noexcept override
	{
		return _pointers + sizeof...(Types);
	}

private:
	std::tuple<Definition<Types>...> _definitions;
	const Definition_base* _pointers[sizeof...(Types)];

	template<std::size_t Index>
	void _fill_pointers() noexcept
	{}
	template<std::size_t Index, typename Type, typename... Others>
	void _fill_pointers() noexcept
	{
		_pointers[Index] = std::get<Index>(_definitions);
		_fill_pointers<Index + 1, Others...>();
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
