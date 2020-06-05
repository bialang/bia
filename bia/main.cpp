#include <bsl/io.hpp>
#include <bvm/bvm.hpp>
#include <compiler/compiler.hpp>
#include <connector/connector-inl.hpp>
#include <exception/syntax_error.hpp>
#include <gc/gc.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <iostream>
#include <member/function/static_.hpp>
#include <resource/deserialize.hpp>
#include <sstream>
#include <tokenizer/bia_lexer.hpp>
#include <util/finally.hpp>

int main()
{
	auto allocator = std::make_shared<bia::gc::memory::simple_allocator>();
	bia::tokenizer::bia_lexer lexer{ allocator };
	std::stringstream output;
	std::stringstream resources;
	std::stringstream code;
	bia::compiler::compiler compiler{ output, resources };
	auto encoder = bia::string::encoding::get_encoder(bia::string::encoding::standard_encoding::utf_8);
	const auto finally =
	    bia::util::make_finally([encoder] { bia::string::encoding::free_encoder(encoder); });

	code << u8R"(
let x = 34

if not x or 2 {
	print(x)
}

)";

	try {
		lexer.lex(code, *encoder, compiler);
	} catch (const bia::exception::bia_error& e) {
		std::cout << "exception (" << e.name() << "; " << e.filename() << ":" << e.line() << "): " << e.what()
		          << "\n";

		if (dynamic_cast<const bia::exception::syntax_error*>(&e)) {
			const auto details = static_cast<const bia::exception::syntax_error&>(e).details();

			std::cout << details.message << ":" << details.position.operator std::streamoff() << "\n\n"
			          << code.str() << "\n";

			for (auto i = details.position.operator std::streamoff(); i--;) {
				std::cout.put(' ');
			}

			std::cout << "\e[0;32m^\e[0;30m\n";
		}

		return 1;
	}

	compiler.finish();

	BIA_LOG(INFO, "compiling finished");

	auto gc = std::make_shared<bia::gc::gc>(allocator);
	bia::bvm::context context{ gc };
	const auto bytecode = output.str();

	{
		const auto str = static_cast<char*>(gc->allocate(6).release());
		auto name      = gc->construct<bia::member::native::string>(str);
		auto fun = gc->construct<bia::member::function::static_<int (*)(), int>>([](int x) -> int (*)() {
			std::cout << "calculating " << x << " squared\n";

			return [] {
				puts("nested call");

				return 34;
			};
		});

		std::memcpy(str, "print", 6);

		context.symbols().put(name.peek(), fun.peek());
		name.start_monitor();
		fun.start_monitor();
	}

	{
		const auto str = static_cast<char*>(gc->allocate(6).release());
		auto name      = gc->construct<bia::member::native::string>(str);
		auto fun       = gc->construct<bia::member::function::static_<void>>([] {
            std::cout << "starting to collect some dust\n";

            bia::gc::gc::active_gc()->run_once();

            std::cout << "done collecting dust\n";
        });

		std::memcpy(str, "do_gc", 6);

		context.symbols().put(name.peek(), fun.peek());
		name.start_monitor();
		fun.start_monitor();
	}

	{
		const auto str = static_cast<char*>(gc->allocate(3).release());

		std::memcpy(str, "io", 3);

		context.loader().add_module(gc->construct<bia::member::native::string>(str).release(),
		                            gc->construct<bia::bsl::io>(*gc).release());
	}

	bia::bvm::bvm::execute(context,
	                       { reinterpret_cast<const bia::util::byte*>(&bytecode[0]), bytecode.size() },
	                       *bia::resource::deserialize(resources, *gc));

	gc->run_once();
}
