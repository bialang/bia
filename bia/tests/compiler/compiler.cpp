#define CATCH_CONFIG_MAIN

#include <bia/compiler/compiler.hpp>
#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <catch.hpp>
#include <sstream>

using namespace bia;

TEST_CASE("simple compiling", "[compiler]")
{
	/*std::stringstream code;
	std::stringstream output;

	code << u8R"(let x=5)";

	compiler::compiler cp{ output };
	auto encoder =
	    string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
	auto finally = util::make_finally([encoder] { string::encoding::free_encoder(encoder); });
	tokenizer::bia_lexer lexer{ std::make_shared<gc::memory::simple_allocator>() };

	lexer.lex(code, *encoder, cp);
	cp.finish();*/
}
