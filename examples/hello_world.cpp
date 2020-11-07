#include <bia/bia.hpp>
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
	bia::engine engine;
	engine.function(
	    "hello_world", +[] { std::cout << "Hello, World! - C++\n"; });
	engine.use_bsl({ argv, argv + argc });

	std::stringstream code;
	code << u8R"(

// prints 'Hello, World! - Bia' to the console
import io
io.print("Hello, World! - Bia")

// calls the C++ function and prints 'Hello, World - C++' to the console
hello_world()

	)";
	engine.execute(code);
}
