#include "machine_context.hpp"
#include "simple_allocator.hpp"
#include "compiler.hpp"
#include "buffer_output_stream.hpp"
#include "buffer_input_stream.hpp"
#include "syntax.hpp"
#include "disassembler.hpp"
#include "static_function.hpp"
#include "bia.hpp"
#include "disguised_caller.hpp"
#include "class_template.hpp"
#include <chrono>
#include <iostream>
#include <regex>
#include "big_int_allocator.hpp"
#include "cstring_member_def.hpp"
#include "virtual_machine_code.hpp"
#include "variant.hpp"


struct printer
{
	printer(int i)
	{
		a = i;
		printf("default constructor%i\n", i);
	}
	printer(const printer & c)
	{
		a = c.a;
		puts("copy constructor");
	}
	printer(printer&& c)
	{
		a = c.a;
		c.a = 0;
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

auto test()
{
	puts("hello world");

	return 61;
}

int main()
{
	bia::machine::memory::big_int_allocator::initialize(std::make_shared<bia::machine::memory::simple_allocator>());

	{
		// Create context which handles almost everything
		auto _allocator = std::make_shared<machine::memory::simple_allocator>();
		bia::machine::machine_context _context(_allocator, _allocator, _allocator, _allocator);
		
		_context.set_lambda<1>("ser", [](int & i, int j) {
			printf("%i bye %i\n", i, j);
		});
		_context.set_lambda("set", [](const char * i, const char * j) {
			printf("%s bye %s\n", i, j);
		});
		_context.set_lambda("test", [](const printer * p) {
			printf("w: %i\n", p->a);
			//p.a = 34343434;
			return "ho ho how";
		});
		_context.set_lambda<1>("print", [](utility::variant<framework::member*, int64_t, double, const char*> _value) {
			switch (_value.id()) {
			case 1:
				(*_value.get<1>())->print();

				break;
			case 2:
				std::cout << *_value.get<2>() << '\n';

				break;
			case 3:
				std::cout << *_value.get<3>() << '\n';

				break;
			case 4:
				std::cout << *_value.get<4>() << '\n';

				break;
			default:
				puts("");

				break;
			}
		});
		_context.set_lambda("destroy", [](bia::framework::member * _member) {
			_member->undefine();
		});
		_context.set_lambda("defined", [](const bia::framework::member * _member) {
			try {
				_member->flags();
			} catch (const bia::exception::symbol_error&) {
				return false;
			}

			return true;
		});
		_context.set_lambda("time", []() { return std::clock()/(double)CLOCKS_PER_SEC; });
		/*_context.set_lambda("int", [](bia::framework::member * _member) {
			if (_member->flags() & bia::framework::member::F_CSTRING) {
				return std::stoll(static_cast<bia::framework::native::cstring_member<char>*>(_member)->to_cstring(nullptr));
			}

			return _member->to_int();
		});
		_context.set_lambda("float", [](bia::framework::member * _member) {
			if (_member->flags() & bia::framework::member::F_CSTRING) {
				return std::stod(static_cast<bia::framework::native::cstring_member<char>*>(_member)->to_cstring(nullptr));
			}

			return _member->to_double();
		});
		_context.set_lambda("defined", [](const bia::framework::member * _member) {
			try {
				_member->flags();
			} catch (const bia::exception::symbol_error&) {
				return false;
			}

			return true;
		});
		set_class<printer>(_context, "printer")
			.set_constructor<int>()
			.set_function("hey", &test)
			.set_function("hi", &printer::hi);
		*/
		set_class<printer>(_context, "printer").set_constructor<1, int>().set_function("hey", &test).set_function("hi", &printer::hi);

		// Script
		char _script[] = u8R""(

fun foo() {
	print(0)
}

)"";
		/*test_and_time(1, []() {
			bia::dependency::big_int _sum;

			for (auto i = 0; i <= 100000; ++i) {
				if (i % 3 == 0) {
					_sum.add(i * 5);
				} else {
					_sum.multiply(i + 1);
				}
			}
		});*/

		// Compile
		bia::stream::buffer_input_stream _input(std::shared_ptr<const int8_t>(reinterpret_cast<const int8_t*>(_script), [](const int8_t*) {}), sizeof(_script) - 1);
		bia::stream::buffer_output_stream _output;
		bia::compiler::compiler _compiler(_output, _context);

		test_and_time(1, [&]() {
			bia::grammar::syntax::lexer().lex(_input, _compiler, _context);
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

		// Run
		bia::machine::virtual_machine::virtual_machine_code _machine_code({ static_cast<void*>(_output.buffer()), static_cast<size_t>(_output.size()) }, std::move(_compiler.virtual_machine_schein()));

		_machine_code.disassemble();

		system("pause");

		try {
			test_and_time(1, [&] {
				_machine_code.execute();
			});

			//printf("Value of i: %lli\n", _context.get_member("i")->cast<long long>());
		} catch (const std::exception & e) {
			printf("%s: %s\n", typeid(e).name(), e.what());
		}
	}

	system("pause");
}
