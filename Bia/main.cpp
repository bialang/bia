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
#include "class_template.hpp"
#include <chrono>
#include <iostream>
#include <regex>
#include <Windows.h>


struct printer
{
	printer()
	{
		puts("default constructor");
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
};

template<typename _Lambda>
inline void test_and_time(int _count, _Lambda && _lambda)
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
			printf("s%d---%s\n", a, b);
			set_lambda(_context, "ser", []() {
				puts("bye");
			});
			a = 3434.453;
			static printer _p;
			return _p;
		});
		auto _member = _context.emplace_member<framework::object::class_template<printer>>("printer");

		_member->set_constructor();
		_member->emplace_member<framework::executable::static_function<void>>(_context.name_address("hey"), &test);

		//SetConsoleOutputCP(65001);

		// Script
		char _script[] = u8R""(

var i = printer()

print printer
print printer.hey
print printer.lol

)"";

		// Compile
		bia::stream::buffer_input_stream _input(std::shared_ptr<const void>(_script, [](const void*) {}), sizeof(_script) - 1);
		bia::stream::buffer_output_stream _output;
		bia::compiler::compiler _compiler(_output, _context);

		test_and_time(1, [&]() {
			bia::grammar::syntax::interpreter().interpret(_input, _compiler, _context);
		});

		_compiler.finalize();

		// Disassemble
		bia::machine::disassembler _disassembler(&_context);

		_disassembler.disassemble(_output.buffer(), _output.size());

		system("pause");

		// Run
		bia::machine::machine_code _machine_code({ reinterpret_cast<const uint8_t*>(_output.buffer()), _output.size() }, bia::machine::machine_schein(_context.allocator(), _context.executable_allocator()));

		if (_machine_code.is_executable()) {
			// Set active allocator
			bia::machine::machine_context::_active_allocator = _context.allocator();

			try {
				_machine_code.execute();
			} catch (const std::exception & e) {
				printf("%s: %s\n", typeid(e).name(), e.what());
			}
		}
	}

	system("pause");
}