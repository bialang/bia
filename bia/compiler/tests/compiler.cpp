#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <compiler/compiler.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <sstream>
#include <tokenizer/bia_lexer.hpp>
#include <util/finally.hpp>

using namespace bia;

TEST_CASE("simple compiling", "[compiler]")
{
	std::stringstream code;
	std::stringstream output;

	code << u8R"(let x=false)";

	compiler::compiler cp{ output };
	auto encoder =
	    string::encoding::encoder::get_instance(string::encoding::encoder::standard_encoding::utf_8);
	auto finally = util::make_finally([encoder] { string::encoding::encoder::free_instance(encoder); });
	tokenizer::bia_lexer lexer{ std::make_shared<gc::memory::simple_allocator>() };

	lexer.lex(code, *encoder, cp);
	cp.finish();
}