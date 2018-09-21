#include "machine_context.hpp"
#include "simple_allocator.hpp"
#include "simple_executable_allocator.hpp"
#include "compiler.hpp"
#include "buffer_output_stream.hpp"
#include "buffer_input_stream.hpp"
#include "syntax.hpp"
#include "disassembler.hpp"
#include "static_function.hpp"
#include "bia.hpp"
#include "disguised_caller_source.hpp"
#include "class_template.hpp"
#include <chrono>
#include <iostream>
#include <regex>


struct printer
{
	printer(int i)
	{
		a = i;
		printf("default constructor%i\n", i);
	}
	printer(const printer&)
	{
		puts("copy constructor");
	}
	printer(printer&&)
	{
		puts("move constructor");
	}
	~printer()
	{
		puts("destructor");
	}
	void hi()
	{
		printf("hi: %i\n", a);
	}
	int a;
};

template<typename Lambda>
inline void test_and_time(int _count, Lambda && _lambda)
{
	auto _time_taken = 0ll;

	for (auto k = 0; k < _count; ++k)
	{
		auto _start = std::chrono::high_resolution_clock::now();

		_lambda();

		_time_taken += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _start).count();
	}

	printf("Time taken: %f ms\n", _time_taken / static_cast<double>(_count));
}

using namespace bia;

void test()
{
	puts("hello world");
}

int main()
{
	//constructor_chain<const printer>(printer());

	{
		// Create context which handles almost everything
		auto _allocator = std::make_shared<machine::memory::simple_allocator>();
		auto _exec_allocator = std::make_shared<machine::memory::simple_executable_allocator>();
		bia::machine::machine_context _context(_allocator, _exec_allocator);

		set_function(_context, u8"hello_w�rld", static_cast<int(*)(std::string*)>([](std::string *_s) {
			puts(_s->c_str());
			*_s = "alksdalksd";
			return 4;
		}));
		set_lambda(_context, "ser", [&](int & a, const char * b) -> const printer& {
			printf("s%d,%p---%s\n", a, &a, b);
			set_lambda(_context, "ser", []() {
				puts("bye");
			});
			a = 3434.453;
			static printer _p(3);
			return _p;
		});

		set_lambda(_context, "hey", [](double a, double b) {
			puts("hey world");
			printf("%f, %f\n", a, b);
		});

		set_lambda(_context, "o", [](double a) {
			printf("%f\n", a);
		});
		set_class<printer>(_context, "printer").set_constructor<int>().set_function("hey", &test).set_function("hi", &printer::hi);

		//SetConsoleOutputCP(65001);

		// Script
		char _script[] = u8R""(
import time

var _start = time.time_point()

print time.now()



hey(3.4,4.5)
o(43.5)
var i = printer(399)
i.hey()
i.hi()
printer.hey()
print i

var _end = time.time_point()

print time.millis(_start, _end)

)"";

		// Compile
		bia::stream::buffer_input_stream _input(std::shared_ptr<const int8_t>(reinterpret_cast<const int8_t*>(_script), [](const int8_t*) {}), sizeof(_script) - 1);
		bia::stream::buffer_output_stream _output;
		bia::compiler::compiler _compiler(_output, _context);

		test_and_time(1, [&]() {
			bia::grammar::syntax::interpreter().interpret(_input, _compiler, _context);
		});

		_compiler.finalize();

		// Disassemble

		for (auto i = 0; i < _output.size(); ++i) {
			printf("%02x ", static_cast<uint8_t>(_output.buffer()[i]));

			if ((i + 1) % 20 == 0) {
				puts("");
			}
		}
		puts("");
	/*	bia::machine::disassembler _disassembler(&_context);

		_disassembler.disassemble(_output.buffer(), _output.size());
		*/
		system("pause");

		// Run
		bia::machine::machine_code _machine_code({ reinterpret_cast<const uint8_t*>(_output.buffer()), _output.size() }, bia::machine::machine_schein(_context.allocator(), _context.executable_allocator()));

		if (_machine_code.is_executable()) {
			// Set active allocator
			_context.activate_context();

			try {
				_machine_code.execute();
			} catch (const std::exception & e) {
				printf("%s: %s\n", typeid(e).name(), e.what());
			}
		}
	}

	system("pause");
}
