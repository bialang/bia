#include "machine_context.hpp"
#include "simple_allocator.hpp"
#include "compiler.hpp"
#include "buffer_output_stream.hpp"
#include "buffer_input_stream.hpp"
#include "syntax.hpp"

#include <chrono>
#include <iostream>


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
	std::shared_ptr<bia::machine::memory::allocator> _allocator(new bia::machine::memory::simple_allocator());
	std::unique_ptr<bia::machine::machine_context> _context(new bia::machine::machine_context(_allocator));

	char _script[] = R"delim(

print "hello"

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

	/*system("pause");
	return 0;
	//Run(test, 2, 4, 434);
	/*{
		auto time_taken = 0ll;

		for (auto k = 0; k < 20; ++k)
		{
			auto start = std::chrono::high_resolution_clock::now();
			auto sum = 0ll;

			for (auto i = 0; i < 1000000; ++i)
			{
				if (i % 2)
				{
					sum += (i - 1) * 3;
				}
				else
				{
					sum += (i + 1) * 2;
				}
			}

			printf("%lli\n", sum);

			time_taken += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
		}

		printf("%f\n", time_taken / 20.0);
	}*/
	std::shared_ptr<bia::machine::BiaAllocator> pAllocator(new bia::machine::BiaAllocator());
	bia::stream::BiaOutputStreamBuffer buf;
	std::unique_ptr<bia::machine::BiaMachineContext> pContext(new bia::machine::BiaMachineContext(pAllocator));
	int my_var = 10;
	pContext->SetLambda("hello_world", [&]() -> int& {
		printf("Hello, World! - C++ %p is %i\n", &my_var, my_var);
		return my_var;
	});

//var i = 65*65+5*8;
	constexpr auto TEST_TIMES = 1;
	char script[] = R"delim(

global v = hello_world()
v = 6374
hello_world()

)delim";
	pContext->SetScript("test", script, sizeof(script) - 1);
	pContext->ExecuteScript("test");
	/*
	global i = 0
global j = new obj()
p=0+i*i

#rest
#global source = con.get_source()
#global pre = find_between(source, R"(<link rel="canonical" href=")", R"(")") + "images"
#global images = find_all_between(source, R"(<td><a href="images)", R"(")")
#
#global i = 0
#
#while check_size(i, images) {
#	con.save(pre + images.at(i))
#	
#	i += 1
#}

	*/

	std::unique_ptr<bia::machine::BiaMachineCode> pCode;
	bia::machine::BiaMachineSchein schein(nullptr);

	try
	{
		bia::compiler::BiaCompiler compiler(buf, *pContext.get(), pAllocator.get());

		bia::grammar::BiaGrammar::GetGrammar().Interpret(script, sizeof(script) - 1, compiler);
		schein = std::move(compiler.GetMachineSchein());
	}
	catch (bia::exception::Exception & e)
	{
		e.Print();

		system("pause");

		return 2;
	}

	pCode.reset(new bia::machine::BiaMachineCode(buf.GetBuffer(), std::move(schein)));
	puts(script);
	
	printf("address: %p\n", pContext.get());


	auto buffer = buf.GetBuffer();
	int t = 0;

	printf("Code Size: %zi\n", buffer.second);

	while (buffer.second--)
	{
		printf("%02hhx ", *buffer.first++);

		if (++t == 20)
		{
			puts("");
			t =0 ;
		}
	}
	if (t != 0)
	{
		puts("");
	}

	puts("--BEGIN--");
	buffer = buf.GetBuffer();
	try
	{
		bia::machine::disassembler::BiaMachineDecoder decoder(pContext.get(), pContext->m_index);
		decoder.Disassemble(buffer.first, buffer.second);
	}
	catch (const bia::exception::Exception & e)
	{
		e.Print();
	}
	
	puts("--END--");

	
	system("pause");

	try
	{
		Test(TEST_TIMES, [&] {
			pCode->Execute();
		});

		//context.Run("global o = 61;", 14);
		//printf("Retrieved i: %i\n", *pContext->GetGlobal("c")->Cast<int>());
	}
	catch (const bia::exception::Exception & e)
	{
		e.Print();
	}
	catch (const std::exception & e)
	{
		puts(e.what());
	}
	catch (...)
	{
		puts("Something was thrown");
	}
	pContext.reset();
	system("pause");
}