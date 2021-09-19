#include <bia/cbia.h>
#include <stdio.h>
#include <stdlib.h>

static void hello_world(bia_function_context_t context, void* arg)
{
	puts("Hello, World! - C");
	char* s;
	bia_function_context_get_string(context, 0, &s);
	puts(s);
	free(s);
}

int main(int argc, char** argv)
{
	const char code[] = "hello_world(\"hi\")";

	bia_engine_t engine = bia_engine_new();

	// create custom function
	bia_signature_t signature = bia_signature_new(bia_standard_definition(engine, BIA_DEF_VOID), NULL);
	bia_signature_push_argument(signature, bia_standard_definition(engine, BIA_DEF_STRING));
	bia_engine_put_function(engine, "hello_world", signature, &hello_world, NULL, true);

	bia_run(engine, code, sizeof(code) - 1);
	bia_engine_free(engine);
}
