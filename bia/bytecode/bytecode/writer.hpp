#pragma once

#include "op_code.hpp"

#include <cstdint>
#include <stream/output_stream.hpp>
#include <util/type_traits/equals_any.hpp>
#include <util/type_traits/int_maker.hpp>

namespace bia {
namespace bytecode {

template<typename T>
inline IMMEDIATE_INT_OP_CODE_OPTION index_of_immediate_int() noexcept
{
	constexpr auto index = util::type_traits::equals_any_type<T, std::int8_t, std::int32_t>::value;

	static_assert(index != 0, "invalid immediate int type");

	return static_cast<IMMEDIATE_INT_OP_CODE_OPTION>(index - 1);
}

template<typename T>
inline IMMEDIATE_OP_CODE_OPTION index_of_immediate() noexcept
{
	constexpr auto index = util::type_traits::equals_any_type<T, std::int8_t, std::int32_t, std::int64_t, double,
															  test_register, string_index>::value;

	static_assert(index != 0, "invalid immediate type");

	return static_cast<IMMEDIATE_OP_CODE_OPTION>(index - 1);
}

template<OP_CODE Op_code>
inline typename std::enable_if<bia::util::type_traits::equals_any<OP_CODE, Op_code, OC_RETURN_VOID>::value, void>::type
	write_instruction(bia::stream::output_stream& output)
{
	output.write_all(Op_code);
}

template<OP_CODE Op_code, typename T>
inline typename std::enable_if<
	bia::util::type_traits::equals_any<OP_CODE, Op_code, OC_JUMP, OC_JUMP_TRUE, OC_JUMP_FALSE>::value, void>::type
	write_instruction(bia::stream::output_stream& output, T value)
{
	output.write_all(static_cast<OP_CODE>(Op_code - index_of_immediate_int<T>()), value);
}

template<OP_CODE Op_code, typename T>
inline typename std::enable_if<
	bia::util::type_traits::equals_any<OP_CODE, Op_code, OC_PUSH_IMMEDIATE, OC_RETURN_IMMEDIATE>::value, void>::type
	write_instruction(bia::stream::output_stream& output, T value)
{
	output.write_all(static_cast<OP_CODE>(Op_code - index_of_immediate<T>()), value);
}

template<op_code_type... Ints>
inline void forward_end(stream::output_stream& output, util::type_traits::int_container<op_code_type, Ints...>)
{
	output.write_all(Ints...);
}

inline void write_end(stream::output_stream& output)
{
	forward_end(
		output,
		util::type_traits::int_filler<op_code_type, (max_instruction_size / sizeof(op_code_type) + sizeof(op_code_type)),
									 OC_RETURN_VOID>::values);
}

} // namespace bytecode
} // namespace bia