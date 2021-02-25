#ifndef BIA_BVM_OPERATIONS_HPP_
#define BIA_BVM_OPERATIONS_HPP_

#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <cstddef>
#include <regex>
#include <type_traits>

namespace bia {
namespace bvm {

struct Plus
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left + right;
	}
};

struct Minus
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left - right;
	}
};

struct Multiplies
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left * right;
	}
};

struct Divides
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left / right;
	}
};

struct Equal_to
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left == right;
	}
	bool operator()(memory::gc::GC_able<memory::gc::String*> left,
	                memory::gc::GC_able<memory::gc::String*> right) const noexcept
	{
		return left->string == right->string;
	}
	bool operator()(memory::gc::GC_able<memory::gc::Regex*> left,
	                memory::gc::GC_able<memory::gc::String*> right) const noexcept
	{
		return std::regex_match(right->string, left->pattern);
	}
};

struct Not_equal_to
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left != right;
	}
	bool operator()(memory::gc::GC_able<memory::gc::String*> left,
	                memory::gc::GC_able<memory::gc::String*> right) const noexcept
	{
		return left->string != right->string;
	}
	bool operator()(memory::gc::GC_able<memory::gc::Regex*> left,
	                memory::gc::GC_able<memory::gc::String*> right) const noexcept
	{
		return !std::regex_match(right->string, left->pattern);
	}
};

struct Inside_of
{
	bool operator()(memory::gc::GC_able<memory::gc::String*> left,
	                memory::gc::GC_able<memory::gc::String*> right) const noexcept
	{
		return right->string.find(left->string) != std::string::npos;
	}
	bool operator()(memory::gc::GC_able<memory::gc::Regex*> left,
	                memory::gc::GC_able<memory::gc::String*> right) const noexcept
	{
		return std::regex_search(right->string, left->pattern);
	}
};

template<bool Left>
struct Select_arg
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return Left ? left : right;
	}
};

} // namespace bvm
} // namespace bia

#endif
