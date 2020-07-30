#include <bia/cbia.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	bia_engine_t engine = bia_engine_new();

	bia_engine_use_bsl(engine, (const char* const*) argv, (size_t) argc);

	const char code[] = "import io; import sys; io.print(sys.version)";

	bia_run(engine, code, sizeof(code) - 1);
	bia_engine_free(engine);
}
