#pragma once

#include <cstdint>

namespace bia {
namespace bytecode {

typedef int op_code_type;
constexpr auto max_instruction_size = 2;

struct string_index
{
	typedef std::uint64_t index_type;

	const index_type index;

	string_index(index_type index) : index(index)
	{}
};

struct test_register
{};

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
	ICOC_INT8,			// a constant 8 bit value
	IOCO_INT32,			// a constant 32 bit value
	IOCO_INT64,			// a constant 64 bit value
	IOCO_FLOAT,			// a constant 64 bit double precision IEEE 754 floating point value
	IOCO_TEST_REGISTER, // the current value in the test register
	IOCO_STRING,		// a string

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

	/* immediate instruction */
	OC_PUSH_IMMEDIATE   = OC_JUMP_FALSE + IOCO_COUNT,	 // pushes an immediate value
	OC_RETURN_IMMEDIATE = OC_PUSH_IMMEDIATE + IOCO_COUNT, // returns an immediate

	/* member instruction */
	OC_PUSH_MEMBER   = OC_RETURN_IMMEDIATE + MOCO_COUNT,
	OC_RETURN_MEMBER = OC_PUSH_MEMBER + MOCO_COUNT,
	OC_TEST			 = OC_RETURN_MEMBER + MOCO_COUNT,

	/* member-immeadiate instruction */
	OC_INSTANTIATE = OC_TEST + MOCO_COUNT * IOCO_COUNT, // instantiates a member with the given immediate

	/* member-member instructions */
	OC_SHALLOW_COPY =
		OC_INSTANTIATE + MOCO_COUNT * MOCO_COUNT, // makes a shallow copy of the second object to the first one
	OC_DEEP_COPY = OC_SHALLOW_COPY + MOCO_COUNT * MOCO_COUNT, // makes a deep copy of the second object to the first one
	OC_REFER	 = OC_DEEP_COPY + MOCO_COUNT * MOCO_COUNT,	// makes a references
};

} // namespace bytecode
} // namespace bia