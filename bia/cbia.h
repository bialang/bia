#ifndef CBIA_H_
#define CBIA_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum
	{
		BIA_OK = 0,

		BIA_ERR_UNKNOWN = -1,
	} bia_err_t;

	typedef void* bia_context_t;
	typedef void* bia_bytecode_t;

	bia_context_t bia_context_new();
	void bia_context_free(bia_context_t context);

	bia_err_t bia_compile(bia_context_t context, bia_bytecode_t* out, const char* code, size_t size);

	void bia_bytecode_free(bia_bytecode_t bytecode);

	bia_err_t bia_run(bia_context_t context, bia_bytecode_t bytecode);
#ifdef __cplusplus
}
#endif

#endif
