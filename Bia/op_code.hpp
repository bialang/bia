#pragma once

#include <cstdint>


namespace bia
{
namespace virtual_machine
{

typedef uint8_t op_code_type;

enum OP_CODE : op_code_type
{
	/** Returns from the current function. */
	RETURN,
	/** Calls the print function of an member. */
	OCALL_PRINT,
	/** Calls the copy function of an member. */
	OCALL_COPY,
	/** Calls the refer function of an member. */
	OCALL_REFER,
	/** Calls the clone function of an member. */
	OCALL_CLONE,
	/** Calls the test function of an member. */
	OCALL_TEST,
};

}
}