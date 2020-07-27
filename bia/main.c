#include <bia/cbia.h>
#include <stdio.h>

int main()
{
	bia_engine_t engine = bia_engine_new();

	bia_engine_use_bsl(engine);

	const char code[] = "import io; io.print(0)";

	bia_run(engine, code, sizeof(code) - 1);
	bia_engine_free(engine);
}
