#ifndef CBIA_H_
#define CBIA_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef void* bia_engine_t;
	typedef void* bia_parameters_t;
	typedef void(*bia_function_t)(bia_parameters_t, void*);
	typedef void* bia_member_t;

	bia_engine_t bia_engine_new();
	void bia_engine_free(bia_engine_t engine);
	int bia_engine_put_function(bia_engine_t engine, const char* name, bia_function_t function, void* custom_arg);
	int bia_engine_use_bsl(bia_engine_t engine, const char* const* argv, size_t argc);

	int bia_run(bia_engine_t engine, const void* code, size_t length);

	int bia_parameters_count(bia_parameters_t params, size_t* out);
	int bia_parameters_at(bia_parameters_t params, size_t index, bia_member_t* out);
	int bia_parameters_positionals_count(bia_parameters_t params, size_t* out);
	int bia_parameters_kwargs_count(bia_parameters_t params, size_t* out);

	int bia_member_cast_int(bia_member_t member, int* out);
	int bia_member_cast_llong(bia_member_t member, long long* out);
	int bia_member_cast_double(bia_member_t member, double* out);
	int bia_member_cast_cstring(bia_member_t member, const char** out);

#ifdef __cplusplus
}
#endif

#endif
