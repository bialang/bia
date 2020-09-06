#include <bia/cbia.h>

static bia_creation_t sqrt_(bia_parameters_t params, void* arg)
{
	bia_parameters_t param = 0;
	bia_creation_t result  = 0;
	double x               = 1.0;
	double guess           = 1.0;
	bia_parameters_at(params, 0, &param);
	bia_member_cast_double(param, &x);

	for (int i = 0; i < 5; ++i) {
		guess -= (guess * guess - x) / (2 * guess);
	}

	bia_create_double(bia_active_gc(), guess, &result);
	return result;
}

int main(int argc, char** argv)
{
	bia_engine_t engine = bia_engine_new();
	bia_engine_use_bsl(engine, (const char* const*) argv, (size_t) argc);
	bia_engine_put_function(engine, "sqrt", &sqrt_, 0);

	const char code[] = "import io; import sys; io.print(sys.version); io.print(sqrt(9.9))";
	bia_run(engine, code, sizeof(code) - 1);
	bia_engine_free(engine);
}
