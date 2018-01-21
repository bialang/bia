#include "biaMachineCode.hpp"
#include "biaOutputStreamBuffer.hpp"
#include "biaToolset.hpp"

#include "biaGrammar.hpp"
#include "biaCompiler.hpp"
#include "biaMachineDecoder.hpp"
#include <chrono>


void hi(int val, ...)
{
	va_list l;
	va_start(l, val);

	while (val-- > 0)
		printf("%i ", va_arg(l, int));

	va_end(l);
}

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

int main()
{
	{
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
	}

	bia::stream::BiaOutputStreamBuffer buf;
	bia::machine::BiaMachineContext context;
//var i = 65*65+5*8;
	char script[] = R"(
global system = 0;
print system();
)";

	/*
	//Nur für diesen Skript
	include einAnderesSkript;
	import einModul;


	define foo(x, y)
	(default=local) {
		//Alle variablen hier sind lokal
		var i = 0;
		local i = 0;
		global j = 0;

	}

	foo(3, 4);

	//Scopes übernehmen immer die eigenschaften der Parentscopes, außer es wird anders definiert
	(default=global)
	{

	}

	//Alle variablen hier sind global
	var immerGlobal = 0;
	global immerGloabl = 0;
	local lokalFürDiesenSkript = 0;

	//Verfügbare Datentypen
	var int = 0;
	var float = 0.3f;
	var double = 0.43423;
	var instanz = new MeinObjekt();
	var kopieInt = int;
	var callback = foo;

	//Array mit 6 elementen
	var array = [6];
	var array = { 1, 0x2 ,03 ,4.f ,5., "sechs"};

	array.length();
	array.append();
	array[3];

	//Pointer
	var memory = allocate(25);

	//Cast
	var int = *(int*)memory;

	//Referenzen
	var variable = "hi";
	var referenzZumWert = :variable;
	var * refenzezZurVariable = &variable;

	//Verfügbare Abzweigungen
	if (true)
	{
	}
	else if (true)
	{
	}
	else
	{
	}

	var i = true ? 1 : "kartoffel";

	switch (i)
	{
	case 1:
		break;
	case "kartoffel":
		break;
	default:
		break;
	}

	//Verfügbare Schleifen
	for (pure i = 0; i < 10; ++i)
	{

	}

	do
	{

	} while(true);

	do
	{

	} until(true);

	while(true)
	{

	}

	until(true)
	{
	}

	for each (var i in array)
	{
	}

	//Variablen können redeklariert werden
	var einString = "kartoffel";

	//Nicht möglich
	einString = 0;

	//Aber
	var einString = 0;

	//Variablen können auch gelöscht werden
	delete einString;
	
	//Exceptions
	try
	{
	}
	catch(exception e)
	{
	}
	catch all
	{
	}
	finally
	{
	}

	//Anderes
	print "hallo, ";
	println "welt";

	//String format
	println "hi #0! ich bims der #1" # ("welt", "yunus");

	//Jederzeit das Skript stoppen
	exit;

	*/

	a * ptr = new a();
	printf("ad: %p\n", ptr);

/*	{
		bia::machine::architecture::BiaToolset toolset(buf);
		toolset.SafeCall(&hi, 34, 5);
		toolset.SafeCall(a::~a, ptr);
	}*/
	try
	{
		bia::compiler::BiaCompiler compiler(buf, context);

		bia::grammar::InitializeRules().Interpret(script, sizeof(script) - 1, compiler);
	}
	catch (bia::exception::Exception & e)
	{
		e.Print();

		system("pause");

		return 1;
	}
	
	printf("address: %p\n", &context);

	bia::machine::BiaMachineCode code(buf.GetBuffer());

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
		bia::machine::disassembler::BiaMachineDecoder decoder(&context, context.m_index);
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
		code.Execute();
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
	system("pause");
}