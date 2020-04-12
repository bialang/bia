#include <catch.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <memory>
#include <sstream>
#include <tokenizer/token/parse/any_of.hpp>
#include <tokenizer/token/parse/number.hpp>
#include <util/finally.hpp>
#include <utility>

using namespace bia::tokenizer;
using namespace bia::tokenizer::token::parse;
using namespace bia::string::encoding;

template<typename... T>
inline std::shared_ptr<token::parameter> create_parameter(T&&... values)
{
	auto input = std::make_shared<std::stringstream>();
	auto enc   = encoder::get_instance(encoder::standard_encoding::utf_8);
	auto bndl  = std::make_shared<token::bundle>();
	auto manager =
	    std::make_shared<bia::resource::manager>(std::make_shared<bia::gc::memory::simple_allocator>());

	int dummy[sizeof...(values)] = { (*input << values, 0)... };

	return { new token::parameter{ *input, *manager, *enc, *bndl },
		     [input, manager, enc, bndl](token::parameter* ptr) {
		         delete ptr;
		         encoder::free_instance(enc);
		     } };
}

TEST_CASE("any of", "[tokenizer]")
{
	auto pair = any_of(*create_parameter("false"), nullptr, "true", "false");

	REQUIRE(!pair.second);
	REQUIRE(pair.first == 1);
}

TEST_CASE("number", "[tokenizer]")
{
	const auto parse = [](const char* value) {
		auto param = create_parameter(value);

		REQUIRE(!number(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(static_cast<token::token::type>(param->bundle.begin()->value.index()) ==
		        token::token::type::constant_int);

		return param->bundle.begin()->value.get<std::int64_t>();
	};

	REQUIRE(parse("0") == 0);
	REQUIRE(parse("255") == 255);
	REQUIRE(parse("6582") == 6582);
	REQUIRE(parse("9223372036854775807") == 9223372036854775807);
	REQUIRE(number(*create_parameter("9223372036854775808")));
}
