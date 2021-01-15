#include <algorithm>
#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/tokenizer/token/parse/any_of.hpp>
#include <bia/tokenizer/token/parse/tokens.hpp>
#include <bia/util/finally.hpp>
#include <catch.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

using namespace bia::tokenizer::token;
using namespace bia::tokenizer::token::parse;
using namespace bia::error;
using namespace bia::string::encoding;

template<typename... T>
inline std::shared_ptr<parameter> create_parameter(T&&... values)
{
	auto input = std::make_shared<std::stringstream>();
	auto enc   = get_encoder(standard_encoding::utf_8);
	auto bndl  = std::make_shared<std::vector<Token>>();
	auto manager =
	  std::make_shared<bia::resource::Manager>(std::make_shared<bia::gc::memory::simple_allocator>());
	int dummy[sizeof...(values)] = { (*input << values, 0)... };
	return { new parameter{ *input, *manager, *enc, *bndl }, [input, manager, enc, bndl](parameter* ptr) {
		        delete ptr;
		        free_encoder(enc);
		      } };
	return nullptr;
}

TEST_CASE("declaration statement", "[tokenizer]")
{
	Token::number zero{};
	zero.type    = Token::number::type::i;
	zero.value.i = 0;

	auto param = create_parameter("let i = 0");
	REQUIRE(!root(*param));
	REQUIRE(param->bundle.size() == 5);
	REQUIRE(param->bundle[0].value == Token::keyword::let);
	REQUIRE(param->bundle[1].value.is_type<Token::identifier>());
	REQUIRE(param->bundle[2].value == operator_::assign);
	REQUIRE(param->bundle[3].value == zero);
	REQUIRE(param->bundle[4].value == Token::control::cmd_end);

	param = create_parameter("let i = ?");
	REQUIRE(static_cast<bool>(root(*param)));
	REQUIRE(param->bundle.empty());

	param = create_parameter("let i: int = 0");
	REQUIRE(!root(*param));
	REQUIRE(param->bundle.size() == 8);
	REQUIRE(param->bundle[0].value == Token::keyword::let);
	REQUIRE(param->bundle[1].value.is_type<Token::identifier>());
	REQUIRE(param->bundle[2].value == Token::control::type_definition);
	REQUIRE(param->bundle[3].value == Token::array_dimension{ 0 });
	REQUIRE(param->bundle[4].value.is_type<Token::identifier>());
	REQUIRE(param->bundle[5].value == operator_::assign);
	REQUIRE(param->bundle[6].value == zero);
	REQUIRE(param->bundle[7].value == Token::control::cmd_end);
}

TEST_CASE("any of", "[tokenizer]")
{
	const auto pair = any_of(*create_parameter("false"), "true", "false");
	REQUIRE(pair.second);
	REQUIRE(pair.first == 1);
}

TEST_CASE("number", "[tokenizer]")
{
	const auto parse = [](const char* value) {
		const auto param = create_parameter(value);
		REQUIRE(!number(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(param->bundle.front().value.is_type<Token::number>());
		return param->bundle.begin()->value.get<Token::number>();
	};

	auto num = parse("0");
	REQUIRE(num.type == Token::number::type::i);
	REQUIRE(num.value.i == 0);

	num = parse("255");
	REQUIRE(num.type == Token::number::type::i);
	REQUIRE(num.value.i == 255);

	num = parse("22222");
	REQUIRE(num.type == Token::number::type::i);
	REQUIRE(num.value.i == 22222);

	REQUIRE(number(*create_parameter("?")).code == bia::error::Code::bad_number);
	REQUIRE(number(*create_parameter("-")).code == bia::error::Code::bad_number);
	REQUIRE(number(*create_parameter("+")).code == bia::error::Code::bad_number);
}

TEST_CASE("string", "[tokenizer]")
{
	const auto parse = [](const char* p, const char* str) {
		const auto param = create_parameter(p);
		REQUIRE(!string(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(param->bundle.front().value.is_type<Token::string>());

		const auto mem = param->bundle.begin()->value.get<Token::string>().memory;
		REQUIRE(mem.size == std::char_traits<char>::length(str) + 1);
		REQUIRE(std::equal(mem.begin(), mem.end() - 1, str,
		                   [](bia::util::byte_type left, char right) { return static_cast<char>(left) == right; }));
	};

	parse(R"("hello world!")", "hello world!");
	parse(R"("hi\aasd\bqwe\vasd\tasd\fasdw\bqwe\nwqd\rdasd\\awd\"ad\"")",
	      "hi\aasd\bqwe\vasd\tasd\fasdw\bqwe\nwqd\rdasd\\awd\"ad\"");
}

TEST_CASE("identifiers", "[tokenizer]")
{
	REQUIRE(!identifier(*create_parameter("some_id")));
	REQUIRE(identifier(*create_parameter("let")).code == Code::bad_identifier);
	REQUIRE(!identifier(*create_parameter("lettuce")));
	REQUIRE(identifier(*create_parameter("import ")).code == Code::bad_identifier);
}

TEST_CASE("seperators", "[tokenizer]")
{
	const auto consumed = [](const char* str, bool expect_error) -> std::streamoff {
		const auto param = create_parameter(str);
		REQUIRE(static_cast<bool>(spacer(*param)) == expect_error);
		return expect_error ? -1 : static_cast<std::streamoff>(param->input.tellg());
	};

	REQUIRE(consumed(" \t\f\v", false) == 4);
	consumed("asd \r\f", true);
	REQUIRE(consumed("/* kartoffel */asd", false) == 15);
}
