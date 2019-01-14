#pragma once

#include <cstdint>


namespace bia
{
namespace machine
{
namespace virtual_machine
{

typedef uint8_t op_code_t;
typedef uint32_t member_index_t;
typedef uint8_t tiny_member_index_t;


enum OP_CODE_FLAGS : op_code_t
{
	OCF_TINY = 0x1
};

enum OP_CODE : op_code_t
{
	/** Returns from the current function. */
	OC_RETURN,
	OC_CREATE_TEMP_MEMBERS,
	OC_PARAM_M,
	OC_PARAM_T,
	OC_PARAM_L,
	OC_PARAM_tM = OC_PARAM_M | OCF_TINY,
	OC_PARAM_tT = OC_PARAM_T | OCF_TINY,
	OC_PARAM_tL = OC_PARAM_L | OCF_TINY,
	OC_PARAM_I32,
	OC_PARAM_I64,
	OC_PARAM_D,
	OC_INSTANTIATE_0,
	OC_INSTANTIATE_N1,
	OC_INSTANTIATE_1,
	OC_INSTANTIATE_I32,
	/** Calls the copy function of an member. */
	OC_OCALL_COPY,
	/** Calls the refer function of an member. */
	OC_OCALL_REFER,
	/** Calls the clone function of an member. */
	OC_OCALL_CLONE,
	/** Calls the test function of an member. */
	OC_OCALL_TEST,
};

}
}
}