#include <bia/engine.hpp>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char** argv)
{
	bia::Engine engine;
	engine.function("hello_world", [] { std::cout << "Hello, World! - C++\n"; });
	engine.function("print", [](const std::vector<std::string>& ss, std::ptrdiff_t i) {
		for (const auto& s : ss) {
			std::cout << s << " ";
		}
		std::cout << i << "\n";
	});
	engine.function("read", [] {
		std::cout << "Enter a string twice...\n";
		std::string s;
		std::vector<std::string> ss;
		for (int i = 0; i < 2; ++i) {
			std::getline(std::cin, s);
			ss.push_back(s);
		}
		return ss;
	});
	engine.function("append",
	                [](std::vector<std::string>& ss, const std::string& value) { ss.push_back(value); });

	auto args = engine.object("args");
	args.variable("count", std::ptrdiff_t{ argc });
	args.variable("program", std::string{ argv[0] });
	args.finish();

	// auto sys = engine.module("sys");
	// sys.function("exit", &std::exit);
	// sys.finish();

	engine.use_bsl();

	std::stringstream code;
	code << u8R"(

		// let input = read()
		// append(input, args.program)
		// print(input, args.count)
		import io
		import sys
		import math
		io.print("hi", "ich", 34, sys.int_size, math.pi)

	)";
	engine.run(code);
}
