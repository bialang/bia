#include <algorithm>
#include <catch.hpp>
#include <gc/memory/simple_allocator.hpp>
#include <memory>
#include <sstream>
#include <tokenizer/token/parse/any_of.hpp>
#include <tokenizer/token/parse/number.hpp>
#include <tokenizer/token/parse/string.hpp>
#include <tokenizer/token/parse/whitespace_eater.hpp>
#include <util/finally.hpp>
#include <utility>

using namespace bia::tokenizer;
using namespace bia::tokenizer::token::parse;
using namespace bia::string::encoding;

template<typename... T>
inline std::shared_ptr<token::parameter> create_parameter(T&&... values)
{
	auto input = std::make_shared<std::stringstream>();
	auto enc   = get_encoder(standard_encoding::utf_8);
	auto bndl  = std::make_shared<token::bundle>();
	auto manager =
	    std::make_shared<bia::resource::manager>(std::make_shared<bia::gc::memory::simple_allocator>());

	int dummy[sizeof...(values)] = { (*input << values, 0)... };

	return { new token::parameter{ *input, *manager, *enc, *bndl },
		     [input, manager, enc, bndl](token::parameter* ptr) {
		         delete ptr;
		         free_encoder(enc);
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
		const auto param = create_parameter(value);

		REQUIRE(!number(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(static_cast<token::token::type>(param->bundle.begin()->value.index()) ==
		        token::token::type::constant_int);

		return param->bundle.begin()->value.get<token::token::int_type>();
	};

	REQUIRE(parse("0") == 0);
	REQUIRE(parse("255") == 255);
	REQUIRE(parse("6582") == 6582);
	REQUIRE(parse("9223372036854775807") == 9223372036854775807);
	REQUIRE(number(*create_parameter("9223372036854775808")));
}

TEST_CASE("string", "[tokenizer]")
{
	const auto parse = [](const char* p, const char* str) {
		const auto param = create_parameter(p);

		REQUIRE(!string(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(static_cast<token::token::type>(param->bundle.begin()->value.index()) ==
		        token::token::type::constant_string);

		const auto mem = param->bundle.begin()->value.get<token::token::string>().memory;

		REQUIRE(mem.size == std::char_traits<char>::length(str) + 1);
		REQUIRE(std::equal(mem.begin(), mem.end() - 1, str, [](bia::util::byte left, char right) {
			return *reinterpret_cast<char*>(&left) == right;
		}));
	};

	parse(R"("hello world!")", "hello world!");
	parse(R"("hi\aasd\bqwe\vasd\tasd\fasdw\bqwe\nwqd\rdasd\\awd\"ad\"")",
	      "hi\aasd\bqwe\vasd\tasd\fasdw\bqwe\nwqd\rdasd\\awd\"ad\"");
}

TEST_CASE("whitespaces", "[tokenizer]")
{
	const auto consumed = [](const char* str, bool expect_error) -> std::streamoff {
		const auto param = create_parameter(str);

		REQUIRE(eat_whitespaces(*param).valid == expect_error);

		return expect_error ? -1 : static_cast<std::streamoff>(param->input.tellg());
	};

	REQUIRE(consumed(" \t\f\v", false) == 4);
	consumed("asd \r\f", true);
	REQUIRE(consumed(" /* kartoffel */asd", false) == 16);
}
