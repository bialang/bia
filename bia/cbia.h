#ifndef CBIA_H_
#define CBIA_H_

#include <stdbool.h>
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

	typedef enum
	{
		BIA_DEF_VOID,
		BIA_DEF_CHAR,
		BIA_DEF_UNSIGNED_CHAR,
		BIA_DEF_SIGNED_CHAR,
		BIA_DEF_SHORT_INT,
		BIA_DEF_UNSIGNED_SHORT_INT,
		BIA_DEF_INT,
		BIA_DEF_UNSIGNED_INT,
		BIA_DEF_LONG_INT,
		BIA_DEF_UNSIGNED_LONG_INT,
		BIA_DEF_LONG_LONG_INT,
		BIA_DEF_UNSIGNED_LONG_LONG_INT,
		BIA_DEF_FLOAT,
		BIA_DEF_DOUBLE,
		BIA_DEF_LONG_DOUBLE,
	} bia_standard_definition_t;

	typedef void* bia_context_t;
	typedef void* bia_bytecode_t;
	typedef const void* bia_definition_t;
	typedef void* bia_signature_t;
	typedef void (*bia_function_t)(void*);

	bia_context_t bia_context_new();
	void bia_context_free(bia_context_t context);
	/**
	 * Registers a new function for the function which will be globally available inside the Bia code.
	 *
	 * @param context The machine context.
	 * @param name The name of the function. Any existing global value will be overwritten.
	 * @param signature The signature of the function. Dynamically typed functions are not possible.
	 * @param function The function callback.
	 * @param argument An user argument which is passed to the callback when called.
	 * @param immutable Whether the Bia code is allowed to overwrite the value.
	 * @returns An error code.
	 */
	int bia_context_put_function(bia_context_t context, const char* name, bia_signature_t signature,
	                             bia_function_t function, void* argument, bool immutable);

	/// Retrieves the definition for a standard type. Returns null, if an error occurred.
	bia_definition_t bia_standard_definition(bia_standard_definition_t type);

	/// Creates a new signature object with no parameters and a void return.
	bia_signature_t bia_signature_new();
	int bia_signature_set_return(bia_signature_t signature, bia_definition_t definition);
	int bia_signature_set_argument(bia_signature_t signature, int index, bia_definition_t definition);

	bia_err_t bia_compile(bia_context_t context, bia_bytecode_t* out, const char* code, size_t size);

	void bia_bytecode_free(bia_bytecode_t bytecode);

	bia_err_t bia_run(bia_context_t context, bia_bytecode_t bytecode);
#ifdef __cplusplus
}
#endif

#endif
