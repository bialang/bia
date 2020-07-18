#ifndef BIA_BYTECODE_WRITER_VARIATION_HPP_
#define BIA_BYTECODE_WRITER_VARIATION_HPP_

#include "../op_code.hpp"
#include "../option.hpp"

#include <bia/util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {
namespace writer {
namespace detail {

template<int BitOffset>
constexpr op_code_type encode_variations()
{
	return 0;
}

template<int BitOffset, typename Variant, typename... Variants>
constexpr op_code_type encode_variations(Variant variant, Variants... variants)
{
	return variant << (BitOffset - bit_size<Variant>()) |
	       encode_variations<BitOffset - bit_size<Variant>()>(variants...);
}

} // namespace detail

template<op_code OpCode, typename... Variants>
constexpr op_code_type encode_variations(Variants... variants)
{
	return OpCode |
	       detail::encode_variations<(
	           util::type_traits::equals_any<op_code, OpCode, oc_operator, oc_get, oc_test>::value ? 11 : 7)>(
	           variants...);
}

} // namespace writer
} // namespace bytecode
} // namespace bia

#endif
