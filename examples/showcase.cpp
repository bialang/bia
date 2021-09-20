#include <bia/engine.hpp>
#include <iostream>
#include <sstream>

int main()
{
	bia::Engine engine;
	engine.function("sum", [](bia::Varargs<std::ptrdiff_t> args) {
		std::ptrdiff_t sum = 0;
		for (std::ptrdiff_t arg : args) {
			sum += arg;
		}
		return sum;
	});
	engine.make_available("io", bia::bsl::io);

	std::stringstream code;
	code << u8R"(
		import io

		io.print("Sum", sum(1, 2, 3, 61))
	)";
	engine.run(code);
}
