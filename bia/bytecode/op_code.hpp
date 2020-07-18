#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include "option.hpp"

#include <bia/util/type_traits/equals_any.hpp>
#include <bia/util/type_traits/type_select.hpp>
#include <cstdint>
#include <tuple>
#include <type_traits>

namespace bia {
namespace bytecode {

typedef std::int16_t op_code_type;

constexpr auto max_instruction_size = sizeof(op_code_type) + 10;

namespace member {

struct args
{
	std::uint16_t index;
};

struct push
{};

struct global
{
	std::uint16_t index;
};

struct local
{
	std::uint16_t index;
};

struct resource
{
	std::uint16_t index;
};

enum class builtin : std::uint8_t
{
	list,
	range
};

} // namespace member

struct test_register
{};

enum op_code : op_code_type
{
	/** extended op code variantions */
	oc_operator = 0 << 11, // [mso, mso, mdo](left source, right source, operator, destination)
	oc_get      = 1 << 11, // [mso, ro, mdo](source, name resource, destination)
	oc_test     = 2 << 11, // [mso, mso](operator, left source, right source)

	/** normal op code variations */
	oc_invoke = static_cast<op_code_type>(
	    0x8000 | (0 << 7)), // [mso, mdo](offset, count, kwarg count, source, destination)
	oc_instantiate = static_cast<op_code_type>(0x8000 | (1 << 7)), // [co, mdo](constant, destination)
	oc_refer       = static_cast<op_code_type>(0x8000 | (2 << 7)), // [mso, mdo](source, destination)
	oc_clone       = static_cast<op_code_type>(0x8000 | (3 << 7)), // [mso, mdo](source, destination)
	oc_copy        = static_cast<op_code_type>(0x8000 | (4 << 7)), // [mso, mdo](source, destination)
	oc_self_operator =
	    static_cast<op_code_type>(0x8000 | (5 << 7)), // [mso, mdo](operator, source, destination)
	oc_import      = static_cast<op_code_type>(0x8000 | (6 << 7)),  // [ro, mdo](name resource, destination)
	oc_jump        = static_cast<op_code_type>(0x8000 | (7 << 7)),  // [oo](offset)
	oc_jump_true   = static_cast<op_code_type>(0x8000 | (8 << 7)),  // [oo](offset)
	oc_jump_false  = static_cast<op_code_type>(0x8000 | (9 << 7)),  // [oo](offset)
	oc_name        = static_cast<op_code_type>(0x8000 | (10 << 7)), // [ro](name resource)
	oc_return_void = static_cast<op_code_type>(0x8000 | (11 << 7)), // []()
	oc_invert      = static_cast<op_code_type>(0x8000 | (12 << 7)), // []()
	oc_prep_call   = static_cast<op_code_type>(0x8000 | (13 << 7)), // []()
};

namespace detail {

template<int BitOffset, typename Variation>
constexpr Variation extract_variation(op_code_type x)
{
	return static_cast<Variation>(x >> (BitOffset - bit_size<Variation>()) &
	                              static_cast<std::uint8_t>(~(0xff << bit_size<Variation>())));
}

template<int BitOffset, typename Variation, typename... Parsed>
constexpr std::tuple<Parsed..., Variation> parse(op_code_type x, util::type_traits::type_container<>,
                                                 Parsed... parsed)
{
	return { parsed..., extract_variation<BitOffset, Variation>(x) };
}

template<int BitOffset, typename Variation, typename... Next, typename... Parsed>
constexpr typename std::enable_if<sizeof...(Next), std::tuple<Parsed..., Variation, Next...>>::type
    parse(op_code_type x, util::type_traits::type_container<Next...>, Parsed... parsed)
{
	return parse<BitOffset - bit_size<Variation>(), Next...>(
	    x, util::type_traits::type_select<1, sizeof...(Next) - 1, Next...>::values, parsed...,
	    extract_variation<BitOffset, Variation>(x));
}

} // namespace detail

template<op_code OpCode, typename... Variations>
constexpr std::tuple<Variations...> parse_options(op_code_type x)
{
	return detail::parse<
	    (util::type_traits::equals_any<op_code, OpCode, oc_operator, oc_get, oc_test>::value ? 11 : 7),
	    Variations...>(x,
	                   util::type_traits::type_select<1, sizeof...(Variations) - 1, Variations...>::values);
}

constexpr op_code to_op_code_base(op_code_type x)
{
	static_assert(static_cast<std::int16_t>(0x8000) >> 15 == static_cast<std::int16_t>(0xffff),
	              "foo you C++");

	return static_cast<op_code>(x & ((static_cast<std::int16_t>(x & 0x8000) >> 8) | 0xf800));
}

} // namespace bytecode
} // namespace bia

#endif
