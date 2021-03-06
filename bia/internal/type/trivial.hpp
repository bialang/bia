#ifndef BIA_INTERNAL_TYPE_TRIVIAL_HPP_
#define BIA_INTERNAL_TYPE_TRIVIAL_HPP_

#include "definition.hpp"

#include <bia/util/algorithm.hpp>
#include <cstddef>
#include <type_traits>
#include <typeindex>
#include <typeinfo>

namespace bia {
namespace internal {
namespace type {

template<typename Type>
class Trivial;

class Trivial_base : public Definition
{
protected:
	template<typename>
	friend class Trivial;
	virtual const std::type_index& type_index() const noexcept = 0;
};

template<typename Type>
class Trivial : public Trivial_base
{
public:
	static_assert(alignof(Type) <= alignof(std::max_align_t), "over-aligned types are not allowed");
	static_assert(std::is_trivial<Type>::value, "Type must be trivial");

	bool is_assignable(const Definition* other) const noexcept override
	{
		return false;
	}
	std::size_t size() const noexcept override
	{
		return sizeof(Type);
	}
	std::size_t alignment() const noexcept override
	{
		return alignof(Type);
	}
	int compare(util::Not_null<const Definition*> other) const noexcept override
	{
		const auto n = util::compare(ordinal(), other->ordinal());
		return n == 0 ? util::compare(type_index(), static_cast<const Trivial_base*>(other.get())->type_index())
		              : n;
	}
	int flags() const noexcept override
	{
		return 0;
	}
	unsigned int ordinal() const noexcept override
	{
		// TODO
		std::terminate();
	}
	const std::type_index& type_index() const noexcept override
	{
		return _type_index;
	}

private:
	const std::type_index _type_index{ typeid(Type) };
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
