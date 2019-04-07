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
#include <sstream>
#include <fstream>
#include "big_int_allocator.hpp"
#include "cstring_member_def.hpp"
#include "virtual_machine_code.hpp"
#include "variant.hpp"
#include "bia_function.hpp"


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
		_context.set_lambda("time", []() { return std::clock() / (double)CLOCKS_PER_SEC; });
		_context.set_lambda("disassemble", [](bia::framework::executable::bia_function * _function) { _function->disassemble(); });
		_context.set_lambda("pause", []() { system("pause"); });
		_context.set_lambda("int", [](utility::variant<framework::member*, int64_t, double, const char*> _value) -> int64_t {
			switch (_value.id()) {
			case 1:
				return (*_value.get<1>())->to_int();
			case 2:
				return *_value.get<2>();
			case 3:
				return *_value.get<3>();
			}

			BIA_IMPLEMENTATION_ERROR;
		});
		_context.set_lambda("float", [](utility::variant<framework::member*, int64_t, double, const char*> _value) -> double {
			switch (_value.id()) {
			case 1:
				return (*_value.get<1>())->to_double();
			case 2:
				return *_value.get<2>();
			case 3:
				return *_value.get<3>();
			}

			BIA_IMPLEMENTATION_ERROR;
		});
		_context.set_lambda("defined", [](const bia::framework::member * _member) {
			try {
				_member->flags();
			} catch (const bia::exception::symbol_error&) {
				return false;
			}

			return true;
		});
		_context.set_function("system", &system);
		set_class<printer>(_context, "printer").set_constructor<1, int>().set_function("hey", &test).set_function("hi", &printer::hi);

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

		std::string _script;

		{
			std::stringstream _ss;
			std::ifstream _file("main.bia");

			if (!_file.is_open()) {
				_file = std::ifstream("../main.bia");
			}

			_ss << _file.rdbuf();
			_script = _ss.str();
		}

		// Compile
		bia::stream::buffer_input_stream _input(std::shared_ptr<const int8_t>(reinterpret_cast<const int8_t*>(_script.data()), [](const int8_t*) {}), _script.length());
		bia::stream::buffer_output_stream _output;
		bia::compiler::compiler _compiler(_output, _context, nullptr);

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
		bia::machine::virtual_machine::virtual_machine_code _machine_code({ static_cast<void*>(_output.buffer()), static_cast<size_t>(_output.size()) }, std::move(_compiler.schein()));

		_machine_code.disassemble();

		system("pause");

		machine::stack _stack(_context.allocator(), 1000);

		try {
			machine::virtual_machine::virtual_machine_code::return_t _return;
			test_and_time(1, [&] {
				_machine_code.execute(_stack, nullptr, 0, _return);
			});

			//printf("Value of i: %lli\n", _context.get_member("i")->cast<long long>());
		} catch (const std::exception & e) {
			printf("%s: %s\n", typeid(e).name(), e.what());
		}
	}

	system("pause");
}
