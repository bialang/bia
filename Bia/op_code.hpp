#pragma once

#include <cstdint>


namespace bia
{
namespace machine
{
namespace virtual_machine
{

typedef uint8_t op_code_type;

enum OP_CODE : op_code_type
{
	/** Returns from the current function. */
	OC_RETURN,
	OC_CREATE_TEMP_MEMBERS,
	PUSH,
	/** Calls the print function of an member. */
	OC_OCALL_PRINT,
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