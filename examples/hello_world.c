#include <bia/cbia.h>
#include <stdio.h>

// static bia_creation_t hello_world(bia_parameters_t params, void* arg)
// {
// 	puts("Hello, World! - C");
// 	return 0;
// }

int main(int argc, char** argv)
{
	// bia_engine_t engine = bia_engine_new();
	// bia_engine_use_bsl(engine, (const char* const*) argv, (size_t) argc);
	// bia_engine_put_function(engine, "hello_world", &hello_world, 0);

	const char code[] = "hi()";
	// bia_run(engine, code, sizeof(code) - 1);
	// bia_engine_free(engine);

	bia_context_t context = bia_context_new();
	bia_bytecode_t bytecode;
	bia_compile(context, &bytecode, code, sizeof(code) - 1);

	bia_run(context, bytecode);

	bia_bytecode_free(bytecode);
	bia_context_free(context);
}
