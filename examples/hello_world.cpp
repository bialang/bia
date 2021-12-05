#include <bia/engine.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	bia::Engine engine;
	engine.function("hello_world", [] { std::cout << "Hello, World! - C++\n"; });

	// introduces Bia's standard library (modules like io, sys, math, etc.)
	engine.use_bsl();

	std::stringstream code;
	code << u8R"(

		// prints 'Hello, World' to the console
		import io
		io.print("Hello, World! - Bia")

		// calls the C++ function and print 'Hello, World - C++' to the console
		hello_world()

	)";
	engine.run(code);
}
