#ifndef BIA_BYTECODE_OP_CODE_HPP_
#define BIA_BYTECODE_OP_CODE_HPP_

#include <cstdint>
#include <type_traits>
#include <util/type_traits/equals_any.hpp>

namespace bia {
namespace bytecode {

typedef std::uint8_t op_code_type;
constexpr auto max_instruction_size = sizeof(op_code_type) + 16;

template<typename T,
         typename =
             std::enable_if<util::type_traits::equals_any_type<T, std::uint8_t, std::uint32_t>::value != 0>>
struct temp_member_index
{
	T index;
};

struct string_index
{
	typedef std::uint64_t index_type;

	const index_type index;

	string_index(index_type index) noexcept : index(index)
	{}
};

struct test_register
{};

enum member_op_code_option
{
	moco_tiny_temp,
	moco_temp,

	moco_count
};

enum immediate_int_op_code_option
{
	iioco_int8,
	iioco_int32,

	iioco_count
};

enum immediate_op_code_option
{
	ioco_int8,          // a constant 8 bit value
	ioco_int32,         // a constant 32 bit value
	ioco_int64,         // a constant 64 bit value
	ioco_float,         // a constant 64 bit double precision IEEE 754 floating point value
	ioco_test_register, // the current value in the test register
	ioco_string,        // a string

	ioco_count
};

enum op_code : op_code_type
{
	/* parameter-less instructions */
	oc_return_void, // returns nothing from the BVM

	/* immediate int instructions */
	oc_jump = oc_return_void + iioco_count, // jumps to a relative location
	oc_jump_true =
	    oc_jump + iioco_count, // jumps to a relative location if the test register evaluates to `true`
	oc_jump_false =
	    oc_jump_true + iioco_count, // jumps to a relative location if the test register evaluates to `false`
	oc_pop = oc_jump_false + iioco_count, // pops n elements from the stack

	/* immediate instruction */
	oc_push_immediate   = oc_pop + ioco_count,            // pushes an immediate value
	oc_return_immediate = oc_push_immediate + ioco_count, // returns an immediate

	/* member instruction */
	oc_push_member   = oc_return_immediate + moco_count,
	oc_return_member = oc_push_member + moco_count,
	oc_test          = oc_return_member + moco_count,

	/* member-immeadiate instruction */
	oc_instantiate = oc_test + moco_count * moco_count, // instantiates a member with the given immediate

	/* member-member instructions */
	oc_shallow_copy =
	    oc_instantiate + moco_count * moco_count, // makes a shallow copy of p1 and stores it in p0
	oc_deep_copy =
	    oc_shallow_copy + moco_count * moco_count, // makes a deep copy of the second object to the first one
	oc_refer = oc_deep_copy + moco_count * moco_count, // makes a references

	/* member-member-immediate int-immediate int instructions */
	oc_call = oc_refer + moco_count * moco_count * iioco_count *
	                         iioco_count, // calls the function stored at p1 with p2  parameters and then pops
	                                      // p3 elements from the stack and saves the result to p0
};

} // namespace bytecode
} // namespace bia

#endif