#pragma once

#include "op_code.hpp"

#include <stream/output_stream.hpp>
#include <util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {

template<OP_CODE Op_code>
inline typename std::enable_if<bia::util::type_traits::equals_any<OP_CODE, Op_code, OC_RETURN_VOID>, void>::type
	write_instruction(bia::stream::output_stream& output)
{}

} // namespace bytecode
} // namespace bia