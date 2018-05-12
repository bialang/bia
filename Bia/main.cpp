#include "machine_context.hpp"
#include "simple_allocator.hpp"
#include "simple_executable_allocator.hpp"
#include "compiler.hpp"
#include "buffer_output_stream.hpp"
#include "buffer_input_stream.hpp"
#include "syntax.hpp"

#include <chrono>
#include <iostream>
#include <regex>


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

int main()
{
	std::unique_ptr<bia::machine::machine_context> _context(new bia::machine::machine_context(std::make_shared<bia::machine::memory::simple_allocator>(), std::make_shared<bia::machine::memory::simple_executable_allocator>()));

	char _script[] = R"delim(

print 0

)delim";

	// Compile
	bia::stream::buffer_input_stream _input(std::shared_ptr<const void>(_script, [](const void*) {}), sizeof(_script) - 1);
	bia::stream::buffer_output_stream _output;
	bia::compiler::compiler _compiler(_output);

	bia::grammar::syntax::get_interpreter().interpret(_input, _compiler);

	_compiler.finalize();
	
	bia::machine::machine_code _machine_code = _compiler.get_code();

	if (_machine_code.is_executable()) {
		_machine_code.execute();
	}

	system("pause");
}