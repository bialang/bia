//#define CATCH_CONFIG_MAIN

#include <bia/assembler/disassembler.hpp>
#include <bia/compiler/compiler.hpp>
#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <catch.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace bia;

// TEST_CASE("simple compiling", "[compiler]")
int main()
{
	std::stringstream code;
	// std::ofstream output{ "/home/yunus/Projects/bia/bytecode.generated", std::ios::out | std::ios::binary };
	// std::ofstream resources{ "/home/yunus/Projects/bia/resources.generated", std::ios::out | std::ios::binary
	// };
	std::stringstream output;
	std::stringstream resources;

	code << u8R"(let x=5)";

	compiler::compiler cp{ output, resources };
	auto encoder = string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
	auto finally = util::make_finally([encoder] { string::encoding::free_encoder(encoder); });
	gc::gc g{ std::make_shared<gc::memory::simple_allocator>() };
	tokenizer::bia_lexer lexer{ g.allocator() };

	lexer.lex(code, *encoder, cp);
	cp.finish();

	// disassemble
	const auto ins = output.str();
	resources.seekg(0, std::ios::beg);
	const auto root = resource::deserialize(resources, g);
	util::span<const util::byte*> instructions{ reinterpret_cast<const util::byte*>(ins.data()), ins.size() };
	assembler::disassemble(instructions, *root, std::cout);
}
