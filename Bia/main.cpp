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
#include "big_int_allocator.hpp"
#include "cstring_member_def.hpp"


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

	for (auto k = 0; k < _count; ++k) {
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
	bia::machine::memory::big_int_allocator::initialize(std::make_shared<bia::machine::memory::simple_allocator>());

	{
		// Create context which handles almost everything
		auto _allocator = std::make_shared<machine::memory::simple_allocator>();
		auto _exec_allocator = std::make_shared<machine::memory::simple_executable_allocator>();
		bia::machine::machine_context _context(_allocator, _allocator, _allocator, _exec_allocator);

		set_lambda(_context, "ser", [&](int & a, const char * b) -> const printer& {
			printf("First parameter: %i at %p\n", a, &a);
			printf("Second parameter: %s\n", b);

			set_lambda(_context, "ser", []() {
				puts("bye");
			});

			a = 3434.453;

			static printer _p(3);

			return _p;
		});
		set_lambda(_context, "print", [](bia::framework::member * _member) {
			_member->print();
		});
		set_lambda(_context, "int", [](bia::framework::member * _member) {
			if (_member->flags() & bia::framework::member::F_CSTRING) {
				return std::stoll(static_cast<bia::framework::native::cstring_member<char>*>(_member)->to_cstring(nullptr));
			}

			return _member->to_int();
		});
		set_lambda(_context, "float", [](bia::framework::member * _member) {
			if (_member->flags() & bia::framework::member::F_CSTRING) {
				return std::stod(static_cast<bia::framework::native::cstring_member<char>*>(_member)->to_cstring(nullptr));
			}

			return _member->to_double();
		});
		set_lambda(_context, "destroy", [](bia::framework::member * _member) {
			_member->undefine();
		});
		set_lambda(_context, "defined", [](const bia::framework::member * _member) {
			try {
				_member->flags();
			} catch (const bia::exception::symbol_error&) {
				return false;
			}

			return true;
		});
		set_lambda(_context, "time", []() { return std::time(nullptr); });
		set_class<printer>(_context, "printer")
			.set_constructor<int>()
			.set_function("hey", &test)
			.set_function("hi", &printer::hi);

		// Script
		char _script[] = u8R""(

var start = time()
var sum = 0
var i = 0

until i == 100000 {
	if i % 3 == 0 {
		sum += i * 5
	}
	else sum *= i + 1

	i += 1
}

var end = time()

print end - start
print sum

)"";
		test_and_time(1, []() {
			bia::dependency::big_int _sum;

			for (auto i = 0; i <= 100000; ++i) {
				if (i % 3 == 0) {
					_sum.add(i * 5);
				} else {
					_sum.multiply(i + 1);
				}
			}
		});

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
		system("pause");

		// Run
		bia::machine::machine_code _machine_code({ reinterpret_cast<const uint8_t*>(_output.buffer()), _output.size() }, bia::machine::machine_schein(_context.allocator(), _context.executable_allocator()));

		if (_machine_code.is_executable()) {
			// Set active allocator
			_context.activate_context();

			try {
				test_and_time(1, [&] {
					_machine_code.execute();
				});
			} catch (const std::exception & e) {
				printf("%s: %s\n", typeid(e).name(), e.what());
			}
		}
	}

	system("pause");
}
