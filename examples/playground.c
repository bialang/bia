#include <bia/cbia.h>

static bia_err_t sqrt_(bia_function_context_t context, void* arg)
{
	double x     = 1.0;
	double guess = 1.0;
	bia_function_context_get_double(context, 0, &x);

	for (int i = 0; i < 5; ++i) {
		guess -= (guess * guess - x) / (2 * guess);
	}

	return bia_function_context_return_double(context, guess);
}

int main(int argc, char** argv)
{
	bia_engine_t engine = bia_engine_new();
	bia_engine_use_bsl(engine);

	bia_signature_t signature = bia_signature_new(bia_standard_definition(engine, BIA_DEF_DOUBLE), NULL);
	bia_signature_push_argument(signature, bia_standard_definition(engine, BIA_DEF_DOUBLE));
	bia_engine_put_function(engine, "sqrt", signature, &sqrt_, NULL, true);

	const char code[] = "import io; import sys; io.print(\"Bia version\", sys.version); io.print(\"PI\", sqrt(9.86960440109))";
	bia_run(engine, code, sizeof(code) - 1);
	bia_engine_free(engine);
}
