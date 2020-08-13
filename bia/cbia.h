#ifndef CBIA_H_
#define CBIA_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum
	{
		berr_ok                = 0,
		berr_invalid_arguments = 1,
		berr_syntax            = 2,
		berr_out_of_bounds     = 3,
		berr_bad_cast          = 4
	} bia_err_t;

	typedef void* bia_engine_t;
	typedef void* bia_gc_t;
	typedef void* bia_parameters_t;
	typedef void* bia_member_t;
	typedef void* bia_creation_t;
	typedef bia_creation_t (*bia_function_t)(bia_parameters_t, void*);

	bia_engine_t bia_engine_new();
	void bia_engine_free(bia_engine_t engine);
	int bia_engine_put_function(bia_engine_t engine, const char* name, bia_function_t function,
	                            void* custom_arg);
	int bia_engine_use_bsl(bia_engine_t engine, const char* const* argv, size_t argc);
	int bia_engine_put(bia_engine_t engine, bia_member_t name, bia_member_t member);
	bia_gc_t bia_engine_get_gc(bia_engine_t engine);

	int bia_run(bia_engine_t engine, const void* code, size_t length);

	bia_gc_t bia_active_gc();

	int bia_parameters_count(bia_parameters_t params, size_t* out);
	int bia_parameters_at(bia_parameters_t params, size_t index, bia_member_t* out);
	int bia_parameters_positionals_count(bia_parameters_t params, size_t* out);
	int bia_parameters_positionals_at(bia_parameters_t params, size_t index, bia_member_t* out);
	int bia_parameters_kwargs_count(bia_parameters_t params, size_t* out);
	int bia_parameters_kwargs_at(bia_parameters_t params, size_t index, bia_member_t* out);
	int bia_parameters_kwargs_find(bia_parameters_t params, const char* name, bia_member_t* out);

	int bia_member_cast_int(bia_member_t member, int* out);
	int bia_member_cast_llong(bia_member_t member, long long* out);
	int bia_member_cast_double(bia_member_t member, double* out);
	int bia_member_cast_cstring(bia_member_t member, const char** out);

	int bia_create_llong(bia_gc_t gc, long long value, bia_creation_t* out);
	int bia_create_double(bia_gc_t gc, double value, bia_creation_t* out);
	int bia_create_cstring(bia_gc_t gc, const char* value, bia_creation_t* out);
	int bia_create_list(bia_gc_t gc, bia_creation_t* out);
	int bia_create_dict(bia_gc_t gc, bia_creation_t* out);
	int bia_creation_dict_put(bia_creation_t dict, bia_member_t key, bia_member_t value);
	int bia_creation_start_monitoring(bia_creation_t creation);
	void bia_creation_free(bia_creation_t creation);
	bia_member_t bia_creation_peek(bia_creation_t creation);
#ifdef __cplusplus
}
#endif

#endif
