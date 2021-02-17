#ifndef BIA_BVM_NATIVE_OPERATIONS_HPP_
#define BIA_BVM_NATIVE_OPERATIONS_HPP_

#include "instruction_pointer.hpp"

#include <bia/memory/stack.hpp>
#include <cstdint>
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
	constexpr int operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return static_cast<int>(left == right);
	}
};

struct Not_equal_to
{
	template<typename Type>
	constexpr int operator()(Type left, Type right) const noexcept
	{
		static_assert(std::is_pod<Type>::value, "Type must be POD");
		return static_cast<int>(left != right);
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

template<typename Type, bool Signed>
using Nao_type = typename std::conditional<Signed, typename std::make_signed<Type>::type,
                                           typename std::make_unsigned<Type>::type>::type;

template<typename Operation, bool Signed>
inline void native_integral_operation(bvm::Operation op, Instruction_pointer& ip, memory::Stack& stack)
{
	const std::int32_t arg0 = ip.read<std::int32_t>();
	const std::int32_t arg1 = ip.read<std::int32_t>();
	switch (op.size) {
	case 0:
		stack.store(arg0, Operation{}(stack.load<Nao_type<std::uint8_t, Signed>>(arg0),
		                              stack.load<Nao_type<std::uint8_t, Signed>>(arg1)));
		break;
	case 1:
		stack.store(arg0, Operation{}(stack.load<Nao_type<std::uint16_t, Signed>>(arg0),
		                              stack.load<Nao_type<std::uint16_t, Signed>>(arg1)));
		break;
	case 2:
		stack.store(arg0, Operation{}(stack.load<Nao_type<std::uint32_t, Signed>>(arg0),
		                              stack.load<Nao_type<std::uint32_t, Signed>>(arg1)));
		break;
	case 3:
		stack.store(arg0, Operation{}(stack.load<Nao_type<std::uint64_t, Signed>>(arg0),
		                              stack.load<Nao_type<std::uint64_t, Signed>>(arg1)));
		break;
	}
}

template<typename Operation>
inline void native_floating_point_operation(bvm::Operation op, Instruction_pointer& ip, memory::Stack& stack)
{
	const std::int32_t arg0 = ip.read<std::int32_t>();
	const std::int32_t arg1 = ip.read<std::int32_t>();
	switch (op.size) {
	case 0: stack.store(arg0, Operation{}(stack.load<float>(arg0), stack.load<float>(arg1))); break;
	case 1: stack.store(arg0, Operation{}(stack.load<double>(arg0), stack.load<double>(arg1))); break;
	}
}

template<typename Operation, bool Signed>
inline int native_integral_test(bvm::Operation op, Instruction_pointer& ip, memory::Stack& stack)
{
	const std::int32_t arg0 = ip.read<std::int32_t>();
	const std::int32_t arg1 = ip.read<std::int32_t>();
	switch (op.size) {
	case 0:
		return Operation{}(stack.load<Nao_type<std::uint8_t, Signed>>(arg0),
		                   stack.load<Nao_type<std::uint8_t, Signed>>(arg1));
	case 1:
		return Operation{}(stack.load<Nao_type<std::uint16_t, Signed>>(arg0),
		                   stack.load<Nao_type<std::uint16_t, Signed>>(arg1));
	case 2:
		return Operation{}(stack.load<Nao_type<std::uint32_t, Signed>>(arg0),
		                   stack.load<Nao_type<std::uint32_t, Signed>>(arg1));
	case 3:
		return Operation{}(stack.load<Nao_type<std::uint64_t, Signed>>(arg0),
		                   stack.load<Nao_type<std::uint64_t, Signed>>(arg1));
	}
	BIA_ASSERT(false);
}

} // namespace bvm
} // namespace bia

#endif
