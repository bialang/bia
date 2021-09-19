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
		BIA_DEF_STRING,
	} bia_standard_definition_t;

	typedef void* bia_engine_t;
	typedef const void* bia_definition_t;
	typedef void* bia_signature_t;
	typedef void* bia_function_context_t;
	typedef void (*bia_function_t)(bia_function_context_t, void*);

	bia_engine_t bia_engine_new();
	void bia_engine_free(bia_engine_t engine);
	/**
	 * Registers a new function for the function which will be globally available inside the Bia code.
	 *
	 * @param engine Bia's engine.
	 * @param name The name of the function. Any existing global value will be overwritten.
	 * @param signature The signature of the function. Dynamically typed functions are not possible.
	 * @param function The function callback.
	 * @param argument An user argument which is passed to the callback when called.
	 * @param immutable Whether the Bia code is allowed to overwrite the value.
	 * @returns An error code.
	 */
	int bia_engine_put_function(bia_engine_t engine, const char* name, bia_signature_t signature,
	                            bia_function_t function, void* argument, bool immutable);

	int bia_function_context_get_char(bia_function_context_t context, size_t index, char* out);
	int bia_function_context_get_uchar(bia_function_context_t context, size_t index, unsigned char* out);
	int bia_function_context_get_schar(bia_function_context_t context, size_t index, signed char* out);
	int bia_function_context_get_short(bia_function_context_t context, size_t index, short int* out);
	int bia_function_context_get_ushort(bia_function_context_t context, size_t index, unsigned short int* out);
	int bia_function_context_get_int(bia_function_context_t context, size_t index, int* out);
	int bia_function_context_get_uint(bia_function_context_t context, size_t index, unsigned int* out);
	int bia_function_context_get_long(bia_function_context_t context, size_t index, long int* out);
	int bia_function_context_get_ulong(bia_function_context_t context, size_t index, unsigned long int* out);
	int bia_function_context_get_llong(bia_function_context_t context, size_t index, long long int* out);
	int bia_function_context_get_ullong(bia_function_context_t context, size_t index, unsigned long long int* out);
	int bia_function_context_get_float(bia_function_context_t context, size_t index, float* out);
	int bia_function_context_get_double(bia_function_context_t context, size_t index, double* out);
	int bia_function_context_get_long_double(bia_function_context_t context, size_t index, long double* out);
	/// Retrieves a string from the given index. The returned memory must be freed seperatly by calling free().
	int bia_function_context_get_string(bia_function_context_t context, size_t index, char** out);

	/// Retrieves the definition for a standard type. Returns null, if an error occurred.
	bia_definition_t bia_standard_definition(bia_engine_t engine, bia_standard_definition_t type);

	bia_signature_t bia_signature_new(bia_definition_t return_definition, bia_definition_t vararg_definition);
	int bia_signature_push_argument(bia_signature_t signature, bia_definition_t definition);

	bia_err_t bia_run(bia_engine_t engine, const char* code, size_t size);
#ifdef __cplusplus
}
#endif

#endif
