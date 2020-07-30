#include <bia/cbia.h>
#include <stdio.h>

static void hello_world(bia_parameters_t params, void* arg)
{
	puts("Hello, World! - C");
}

int main(int argc, char** argv)
{
	bia_engine_t engine = bia_engine_new();

	bia_engine_use_bsl(engine, (const char* const*) argv, (size_t) argc);
	bia_engine_put_function(engine, "hello_world", &hello_world, (void*) 0);

	const char code[] = "import io; io.print(\"Hello, World! - Bia\"); hello_world()";

	bia_run(engine, code, sizeof(code) - 1);
	bia_engine_free(engine);
}
