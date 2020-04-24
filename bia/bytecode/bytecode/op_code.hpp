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

enum member_destination_option
{
	mdo_tos,
	mdo_global_16,
	mdo_local_16,
	mdo_global_8,
	mdo_local_8,

	mdo_count
};

enum member_source_option
{
	mso_tos,
	mso_args,
	mso_global_16,
	mso_local_16,
	mso_resource_16,
	mso_global_8,
	mso_local_8,
	mso_resource_8,

	mso_count
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
	oc_instantiate = -1 + co_count * mdo_count,              // (constant, member)
	oc_invoke      = oc_instantiate + mso_count * mdo_count, // (uint8, source member, destination member)
	oc_refer       = oc_invoke + mso_count * mdo_count,      // (member, member)
	oc_clone       = oc_refer + mso_count * mdo_count,
	oc_copy        = oc_clone + mso_count * mdo_count, // (member, member)
	oc_operator    = oc_copy + mso_count * mdo_count,

	/** 6 bit variants */
	oc_get = oc_operator + mso_count * ro_count * mdo_count, // (source member, resource, destination member)
	oc_import = oc_get + ro_count * mdo_count,               // (name)

	/** 4 bit variants */
	oc_test = oc_import + mso_count, // (member)

	/** 2 bit variants */
	oc_jump       = oc_test + pso_count,      // (offset)
	oc_jump_true  = oc_jump + pso_count,      // (offset)
	oc_jump_false = oc_jump_true + pso_count, // (offset)

	/** 0 bit variants */
	oc_return_void,
	oc_drop, // (uint8)
};

} // namespace bytecode
} // namespace bia

#endif