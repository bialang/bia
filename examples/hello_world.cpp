#include <bia/bia.hpp>
#include <bia/bsl/io.hpp>
#include <iostream>
#include <sstream>

int main()
{
	bia::engine engine;

	engine.function("hello_world", +[] { std::cout << "Hello, World! - C++\n"; });
	engine.module<bia::bsl::io>("io", engine.gc());

	std::stringstream code;

	code << u8R"(
		// prints 'Hello, World' to the console
		import io
		io.print("Hello, World! - Bia")

		// calls the C++ function and print 'Hello, World - C++' to the console
		hello_world()
	)";

	engine.execute(code);
}
