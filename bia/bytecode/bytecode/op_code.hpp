#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include <cstdint>
#include <type_traits>
#include <util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {

typedef std::uint16_t op_code_type;

constexpr auto max_instruction_size = sizeof(op_code_type) + 10;
constexpr auto member_bits          = 4;
constexpr auto constant_bits        = 4;
constexpr auto size_bits            = 2;

enum member_option
{
	mo_tos,
	mo_args,
	mo_global_8,
	mo_global_16,
	mo_local_8,
	mo_local_16,
	mo_resource_8,
	mo_resource_16,

	mo_count
};

namespace member {

struct tos
{};

struct args
{
	std::uint8_t index;
};

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

} // namespace member

enum constant_option
{
	co_int_8,
	co_int_32,
	co_int_64,
	co_double,

	co_count
};

enum resource_option
{
	ro_8,
	ro_16,
	ro_24,
	ro_32,

	ro_count
};

enum parameter_size_option
{
	pso_8,
	pso_16,
	pso_24,
	pso_32,

	pso_count
};

enum op_code : op_code_type
{
	/** 8 bit variants */
	oc_instantiate = -1 + mo_count * co_count,             // (member, constant)
	oc_refer       = oc_instantiate + mo_count * mo_count, // (member, member)
	oc_copy        = oc_refer + mo_count * mo_count,       // (member, member)
	oc_operator    = oc_copy + mo_count * mo_count,

	/** 6 bit variants */
	oc_get = oc_operator + mo_count * ro_count, // (member, resource)

	/** 4 bit variants */
	oc_invoke = oc_get + mo_count,    // (member, uint8)
	oc_test   = oc_invoke + mo_count, // (member)

	/** 2 bit variants */
	oc_jump       = oc_test + pso_count,      // (offset)
	oc_jump_true  = oc_jump + pso_count,      // (offset)
	oc_jump_false = oc_jump_true + pso_count, // (offset)

	/** 0 bit variants */
	oc_return_void
};

} // namespace bytecode
} // namespace bia

#endif