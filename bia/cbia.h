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

	bia_engine_t bia_engine_new();
	void bia_engine_free(bia_engine_t engine);
	int bia_engine_put_function(bia_engine_t engine, const char* name, bia_function_t function, void* custom_arg);
	int bia_engine_use_bsl(bia_engine_t engine);

	int bia_run(bia_engine_t engine, const void* code, size_t length);

#ifdef __cplusplus
}
#endif

#endif
