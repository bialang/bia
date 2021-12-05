#ifndef BIA_BVM_OPERATIONS_HPP_
#define BIA_BVM_OPERATIONS_HPP_

#include <bia/member/object/string.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <cmath>
#include <cstddef>
#include <regex>
#include <type_traits>

namespace bia {
namespace bvm {

struct Addition
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left + right;
	}
};

struct Subtraction
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left - right;
	}
};

struct Multiplication
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left * right;
	}
};

struct Division
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left / right;
	}
};

struct Remainder
{
	template<typename Type>
	constexpr typename std::enable_if<std::is_integral<Type>::value, Type>::type
	  operator()(Type left, Type right) const noexcept
	{
		return left % right;
	}
	float operator()(float left, float right) const noexcept
	{
		return std::fmod(left, right);
	}
	double operator()(double left, double right) const noexcept
	{
		return std::fmod(left, right);
	}
};

struct Bitwise_and
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left & right;
	}
};

struct Bitwise_or
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left | right;
	}
};

struct Bitwise_xor
{
	template<typename Type>
	constexpr Type operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left ^ right;
	}
};

struct Equality
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left == right;
	}
	bool operator()(memory::gc::GC_able<member::object::String*> left,
	                memory::gc::GC_able<member::object::String*> right) const noexcept
	{
		return left->value() == right->value();
	}
	bool operator()(memory::gc::GC_able<memory::gc::Regex*> left,
	                memory::gc::GC_able<member::object::String*> right) const noexcept
	{
		return std::regex_match(right->value(), left->value);
	}
};

struct Inequality
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left != right;
	}
	bool operator()(memory::gc::GC_able<member::object::String*> left,
	                memory::gc::GC_able<member::object::String*> right) const noexcept
	{
		return left->value() != right->value();
	}
	bool operator()(memory::gc::GC_able<memory::gc::Regex*> left,
	                memory::gc::GC_able<member::object::String*> right) const noexcept
	{
		return !std::regex_match(right->value(), left->value);
	}
};

struct Less
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left < right;
	}
};

struct Less_equality
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left <= right;
	}
};

struct Greater
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left > right;
	}
};

struct Greater_equality
{
	template<typename Type>
	constexpr bool operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return left >= right;
	}
};

struct Inside_of
{
	bool operator()(memory::gc::GC_able<member::object::String*> left,
	                memory::gc::GC_able<member::object::String*> right) const noexcept
	{
		return right->value().find(left->value()) != std::string::npos;
	}
	bool operator()(memory::gc::GC_able<memory::gc::Regex*> left,
	                memory::gc::GC_able<member::object::String*> right) const noexcept
	{
		return std::regex_search(right->value(), left->value);
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
