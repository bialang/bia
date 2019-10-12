#pragma once

#include "op_code.hpp"

#include <cstdint>
#include <stream/output_stream.hpp>
#include <util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {

template<OP_CODE Op_code>
inline typename std::enable_if<bia::util::type_traits::equals_any<OP_CODE, Op_code, OC_RETURN_VOID>::value, void>::type
	write_instruction(bia::stream::output_stream& output)
{
	output.write_all(Op_code);
}

template<OP_CODE Op_code, typename T>
inline typename std::enable_if<
	bia::util::type_traits::equals_any<OP_CODE, Op_code, OC_JUMP, OC_JUMP_TRUE, OC_JUMP_FALSE>::value &&
		bia::util::type_traits::equals_any_type<T, std::int8_t, std::int32_t>::value,
	void>::type
	write_instruction(bia::stream::output_stream& output, T value)
{
	output.write_all(Op_code, value);
}

template<OP_CODE Op_code, typename T>
inline typename std::enable_if<
	bia::util::type_traits::equals_any<OP_CODE, Op_code, OC_PUSH_IMMEDIATE, OC_RETURN_IMMEDIATE>::value &&
		bia::util::type_traits::equals_any_type<T, std::int8_t, std::int32_t, std::int64_t, double,
												test_register, string_index>::value,
	void>::type
	write_instruction(bia::stream::output_stream& output, T value)
{
	output.write_all(Op_code, value);
}

} // namespace bytecode
} // namespace bia