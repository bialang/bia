#ifndef BIA_BVM_NATIVE_OPERATIONS_HPP_
#define BIA_BVM_NATIVE_OPERATIONS_HPP_

#include "instruction_pointer.hpp"

#include <bia/memory/frame.hpp>
#include <cstdint>
#include <type_traits>

namespace bia {
namespace bvm {

template<typename Type, bool Signed>
using Nao_type = typename std::conditional<Signed, typename std::make_signed<Type>::type,
                                           typename std::make_unsigned<Type>::type>::type;

template<typename Operation, bool Signed>
inline void native_integral_operation(bvm::Operation op, Instruction_pointer& ip, memory::Frame& frame)
{
	const std::int32_t arg0 = ip.read<std::int32_t>();
	const std::int32_t arg1 = ip.read<std::int32_t>();
	switch (op.variation) {
	case 0:
		frame.store(arg0, Operation{}(frame.load<Nao_type<std::uint8_t, Signed>>(arg0),
		                              frame.load<Nao_type<std::uint8_t, Signed>>(arg1)));
		break;
	case 1:
		frame.store(arg0, Operation{}(frame.load<Nao_type<std::uint16_t, Signed>>(arg0),
		                              frame.load<Nao_type<std::uint16_t, Signed>>(arg1)));
		break;
	case 2:
		frame.store(arg0, Operation{}(frame.load<Nao_type<std::uint32_t, Signed>>(arg0),
		                              frame.load<Nao_type<std::uint32_t, Signed>>(arg1)));
		break;
	case 3:
		frame.store(arg0, Operation{}(frame.load<Nao_type<std::uint64_t, Signed>>(arg0),
		                              frame.load<Nao_type<std::uint64_t, Signed>>(arg1)));
		break;
	}
}

template<typename Operation>
inline void native_floating_point_operation(bvm::Operation op, Instruction_pointer& ip, memory::Frame& frame)
{
	const std::int32_t arg0 = ip.read<std::int32_t>();
	const std::int32_t arg1 = ip.read<std::int32_t>();
	switch (op.variation) {
	case 0: frame.store(arg0, Operation{}(frame.load<float>(arg0), frame.load<float>(arg1))); break;
	case 1: frame.store(arg0, Operation{}(frame.load<double>(arg0), frame.load<double>(arg1))); break;
	}
}

template<typename Operation, bool Signed>
inline bool native_integral_test(bvm::Operation op, Instruction_pointer& ip, memory::Frame& frame)
{
	const std::int32_t arg0 = ip.read<std::int32_t>();
	const std::int32_t arg1 = ip.read<std::int32_t>();
	switch (op.variation) {
	case 0:
		return Operation{}(frame.load<Nao_type<std::uint8_t, Signed>>(arg0),
		                   frame.load<Nao_type<std::uint8_t, Signed>>(arg1));
	case 1:
		return Operation{}(frame.load<Nao_type<std::uint16_t, Signed>>(arg0),
		                   frame.load<Nao_type<std::uint16_t, Signed>>(arg1));
	case 2:
		return Operation{}(frame.load<Nao_type<std::uint32_t, Signed>>(arg0),
		                   frame.load<Nao_type<std::uint32_t, Signed>>(arg1));
	case 3:
		return Operation{}(frame.load<Nao_type<std::uint64_t, Signed>>(arg0),
		                   frame.load<Nao_type<std::uint64_t, Signed>>(arg1));
	}
	BIA_ASSERT(false);
}

} // namespace bvm
} // namespace bia

#endif