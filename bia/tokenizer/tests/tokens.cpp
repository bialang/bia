#include <catch.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <sstream>
#include <tokenizer/token/parse/any_of.hpp>
#include <util/finally.hpp>

using namespace bia::tokenizer;
using namespace bia::tokenizer::token;
using namespace bia::string::encoding;

TEST_CASE("any of", "[tokenizer]")
{
	std::stringstream code{ u8"false" };
	resource::manager manager{ std::make_shared<bia::gc::memory::simple_allocator>() };
	auto enc     = encoder::get_instance(encoder::standard_encoding::utf_8);
	auto finally = bia::util::make_finally([enc] { encoder::free_instance(enc); });
	bundle bndl;
	parameter param{ code, manager, *enc, bndl };

	auto pair = parse::any_of(param, nullptr, "true", "false");

	REQUIRE(!pair.second);
	REQUIRE(pair.first == 1);
}