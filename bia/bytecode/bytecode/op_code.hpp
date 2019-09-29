#pragma once

#include <cstdint>

namespace bia {
namespace bytecode {

typedef int op_code_type;
constexpr auto max_instruction_size = 2;

enum MEMBER_OP_CODE_OPTION
{
	MOCO_LOCAL,
	MOCO_TEMPORARY,
	MOCO_TINY_LOCAL,
	MOCO_TINY_TEMPORARY,

	MOCO_COUNT
};

enum IMMEDIATE_INT_OP_CODE_OPTION
{
	IIOCO_INT8,
	IIOCO_INT32,

	IIOCO_COUNT
};

enum IMMEADIATE_OP_CODE_OPTION
{
	ICOC_INT8,
	IOCO_INT32,
	IOCO_INT64,

	IOCO_COUNT
};

enum OP_CODE : op_code_type
{
	/* parameter-less instructions */
	OC_RETURN_VOID, // returns nothing from the BVM

	/* immediate int parameter instructions */
	OC_JUMP		 = OC_RETURN_VOID + IIOCO_COUNT, // jumps to a relative location
	OC_JUMP_TRUE = OC_JUMP + IIOCO_COUNT, // jumps to a relative location if the test register evaluates to `true`
	OC_JUMP_FALSE =
		OC_JUMP_TRUE + IIOCO_COUNT, // jumps to a relative location if the test register evaluates to `false`

	/* member-immeadiate instruction */
	OC_INSTANTIATE = MOCO_COUNT * IOCO_COUNT, // instantiates a member with the given immediate

	/* member-member instructions */
	OC_CLONE		= MOCO_COUNT * MOCO_COUNT,			  // clones the second member to the first
	OC_SHALLOW_COPY = OC_CLONE + MOCO_COUNT * MOCO_COUNT, // makes a shallow copy of the second object to the first one
	OC_DEEP_COPY = OC_SHALLOW_COPY + MOCO_COUNT * MOCO_COUNT, // makes a deep copy of the second object to the first one
	OC_REFER	 = OC_DEEP_COPY + MOCO_COUNT * MOCO_COUNT,	// makes a references
};

} // namespace bytecode
} // namespace bia