#include "biaMachineCode.hpp"
#include "biaOutputStreamBuffer.hpp"
#include "biaToolset.hpp"

#include "biaGrammar.hpp"
#include "biaCompiler.hpp"
#include "biaMachineDecoder.hpp"
#include <chrono>
#include "biaDisguisedCaller.hpp"
#include "biaInt.hpp"


struct a
{
	virtual ~a()
	{
		puts("destroy a");
	}
	virtual void da(int p)
	{
		printf("hi from a at %p to %i\n", this, p);
	}
};

struct b : a
{
	~b()
	{
		puts("destroy b");
	}
	virtual void da(int p) override
	{
		printf("hi from b at %p to %i\n", this, p);
	}
};

void lua(int a, float b)
{
	printf("a: %i b; %f\n", a, b);
}

void test(int a, int b)
{
	printf("%i, %i\n", a, b);
}
template<typename... _ARGS>
void Run(void(*foo)(_ARGS...), int n, ...)
{
	va_list vl;
	va_start(vl, n);

	foo(*reinterpret_cast<int*>(vl), *reinterpret_cast<int*>(vl + sizeof(int)));
	//auto sa = va_arg(vl, int);
	foo(*(int*)((vl += sizeof(int)) - sizeof(int)), (*(int*)((vl += sizeof(int)) - sizeof(int))));
	// foo((va_arg(vl, _ARGS),...));

	va_end(vl);
}

template<typename _LAMBDA>
inline void Test(int p_nCount, _LAMBDA && p_lambda)
{
	auto time_taken = 0ll;

	for (auto k = 0; k < p_nCount; ++k)
	{
		auto start = std::chrono::high_resolution_clock::now();

		p_lambda();

		time_taken += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	}

	printf("Time taken: %f ms\n", time_taken / static_cast<double>(p_nCount));
}
//7573
int main()
{
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
	int my_var = 3;
	pContext->SetLambda("hello_world", [&]() -> int& {
		printf("Hello, World! - C++ %p\n", &my_var);
		return my_var;
	});
//var i = 65*65+5*8;
	constexpr auto TEST_TIMES = 1;
	char script[] = R"delim(

# Print from Bia
print "Hello, World! - Bia"

# Print from C++
global a = hello_world()

print a

)delim";
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
		//printf("Retrieved i: %i\n", *context.GetGlobal("a")->Cast<int>());
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